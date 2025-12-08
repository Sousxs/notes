// Paciência em modo texto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define DECK_SIZE 52
#define MAX_PILE 52

// 1: estoque (stock), 2: descarte (waste), 3: inexistente, 4-7: fundações (foundations), 21-27: colunas (tableau)
typedef enum {
	COPAS = 0, 
	OUROS = 1, 
	PAUS  = 2, 
	ESPADAS = 3
} Naipe;

typedef struct {
	int valor;     
	Naipe naipe;   
	bool faceUp;   
} Carta;

typedef struct {
	Carta itens[MAX_PILE];
	int top; 
} Pilha;

static void pilha_init(Pilha *p) { p->top = -1; }
static bool pilha_vazia(const Pilha *p) { return p->top < 0; }
static bool pilha_cheia(const Pilha *p) { return p->top >= MAX_PILE - 1; }
static bool pilha_push(Pilha *p, Carta c) { if (pilha_cheia(p)) return false; p->itens[++p->top] = c; return true; }
static bool pilha_pop(Pilha *p, Carta *out) { if (pilha_vazia(p)) return false; if (out) *out = p->itens[p->top]; p->top--; return true; }
static bool pilha_top(const Pilha *p, Carta *out) { if (pilha_vazia(p)) return false; if (out) *out = p->itens[p->top]; return true; }
static int  pilha_tamanho(const Pilha *p) { return p->top + 1; }

static bool carta_e_vermelha(Carta c) { return (c.naipe == COPAS || c.naipe == OUROS); }
static const char* naipe_str(Naipe n) {
	switch (n) {
		case COPAS: return "C";
		case OUROS: return "O"; 
		case PAUS: return "P"; 
		case ESPADAS: return "E"; 
		default: return "?";
	}
}
static const char* valor_str(int v) {
	switch (v) {
		case 1: return "A";
		case 11: return "J";
		case 12: return "Q";
		case 13: return "K";
		default: {
			static char buf[3];
			snprintf(buf, sizeof(buf), "%d", v);
			return buf;
		}
	}
}

static const char* naipe_simbolo(Naipe n) {
	switch (n) {
		case COPAS: return "C";     
		case OUROS: return "O";     
		case PAUS: return "P";      
		case ESPADAS: return "E";   
		default: return "?";
	}
}

// Impressão de uma carta como texto compacto
static void print_carta_compacta(Carta c) {
	if (!c.faceUp) {
		// verso com estampa '##'
		printf("[##]");
	} else {
		printf("[%s%s]", valor_str(c.valor), naipe_simbolo(c.naipe));
	}
}

// Embaralhamento
static void gerar_baralho(Carta baralho[DECK_SIZE]) {
	int idx = 0;
	for (int n = 0; n < 4; n++) {
		for (int v = 1; v <= 13; v++) {
			baralho[idx].valor = v;
			baralho[idx].naipe = (Naipe)n;
			baralho[idx].faceUp = false; // por padrão, verso
			idx++;
		}
	}
}

static void embaralhar(Carta baralho[DECK_SIZE]) {
	for (int i = DECK_SIZE - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		Carta tmp = baralho[i];
		baralho[i] = baralho[j];
		baralho[j] = tmp;
	}
}

// Estado do jogo
typedef struct {
	Pilha estoque;     // 1
	Pilha descarte;    // 2
	Pilha fund[4];     // 4..7
	Pilha tab[7];      // 21..27
	int viradasPorVez; // 1 ou 3
} Jogo;

// Distribuição inicial conforme regras
static void distribuir_inicial(Jogo *j) {
	pilha_init(&j->estoque);
	pilha_init(&j->descarte);
	for (int i = 0; i < 4; i++) pilha_init(&j->fund[i]);
	for (int i = 0; i < 7; i++) pilha_init(&j->tab[i]);

	Carta baralho[DECK_SIZE];
	gerar_baralho(baralho);
	embaralhar(baralho);

	int pos = 0;
	// Montar tableaux 21..27
	for (int col = 0; col < 7; col++) {
		// cartas viradas para baixo
		for (int k = 0; k < col; k++) {
			Carta c = baralho[pos++];
			c.faceUp = false;
			pilha_push(&j->tab[col], c);
		}
		// carta do topo virada para cima
		Carta c = baralho[pos++];
		c.faceUp = true;
		pilha_push(&j->tab[col], c);
	}
	// Restante no estoque (verso)
	while (pos < DECK_SIZE) {
		Carta c = baralho[pos++];
		c.faceUp = false;
		pilha_push(&j->estoque, c);
	}
}

// Regras de movimento
static bool pode_ir_para_fundacao(const Pilha *fund, Carta c) {
	if (pilha_vazia(fund)) {
		return c.valor == 1; // Ás
	}
	Carta topo; pilha_top(fund, &topo);
	return (c.naipe == topo.naipe) && (c.valor == topo.valor + 1);
}

static bool pode_empilhar_em_tableau(const Pilha *tab, Carta c) {
	if (pilha_vazia(tab)) {
		return c.faceUp; // vazio aceita qualquer cartão desde que a base esteja com anverso
	}
	Carta topo; pilha_top(tab, &topo);
	if (!topo.faceUp) return false; // não recebe enquanto topo estiver com verso
	// precisa ser predecessor e cor diferente
	bool corDif = (carta_e_vermelha(c) != carta_e_vermelha(topo));
	return corDif && (c.valor + 1 == topo.valor);
}

// Verifica se um trecho superior do tableau (quantidade cartas) forma sequência válida descendente e alternando cores
static bool sequencia_valida_para_mover(const Pilha *src, int qtd) {
	if (qtd <= 0) return false;
	if (pilha_tamanho(src) < qtd) return false;
	int start = src->top - qtd + 1;
	// todas devem estar viradas para cima
	for (int i = start; i <= src->top; i++) {
		if (!src->itens[i].faceUp) return false;
	}
	// checar sequência descendente e cores alternadas dentro do grupo
	for (int i = start; i < src->top; i++) {
		Carta a = src->itens[i];
		Carta b = src->itens[i + 1];
		if (!(carta_e_vermelha(a) != carta_e_vermelha(b) && a.valor == b.valor + 1)) {
			return false;
		}
	}
	return true;
}

// Desenhar o layout do jogo
static void desenhar(const Jogo *j) {
	printf("\n");
	printf("+================================================================+\n");
	printf("|                    *** PACIENCIA ***                           |\n");
	printf("|  Viradas por vez: %d                                            |\n", j->viradasPorVez);
	printf("+================================================================+\n");
	
	printf("|\n");
	printf("|  ESTOQUE        DESCARTE           FUNDACOES\n");
	printf("|    (1)            (2)         (4)  (5)  (6)  (7)\n");
	printf("|  ");
	
	// Monte 1 (estoque)
	if (!pilha_vazia(&j->estoque)) {
		print_carta_compacta((Carta){.faceUp=false});
	} else {
		printf("    [  ]");
	}
	printf("            ");
	
	// Monte 2 (descarte): mostra 1..3 cartas
	int nDesc = pilha_tamanho(&j->descarte);
	int mostrar = j->viradasPorVez < nDesc ? j->viradasPorVez : nDesc;
	if (mostrar == 0) {
		printf("[  ]");
	} else {
		int start = nDesc - mostrar;
		for (int i = start; i < nDesc; i++) {
			Carta c = j->descarte.itens[i];
			print_carta_compacta(c);
			printf("  ");
		}
	}
	printf("         ");
	
	// Fundações 4..7
	for (int f = 0; f < 4; f++) {
		if (!pilha_vazia(&j->fund[f])) {
			Carta c; pilha_top(&j->fund[f], &c);
			print_carta_compacta(c);
		} else {
			printf("[  ]");
		}
		printf(" ");
	}
	printf("\n|\n");
	printf("+================================================================+\n");
	printf("|                      TABLEAUS (21-27):\n");
	printf("|   21       22       23       24       25       26       27\n");
	printf("|");

	// Segunda linha: 21..27 (tableau)
	// Determinar altura máxima
	int alturas[7]; int maxAlt = 0;
	for (int t = 0; t < 7; t++) { 
		alturas[t] = pilha_tamanho(&j->tab[t]); 
		if (alturas[t] > maxAlt) maxAlt = alturas[t]; 
	}
	
	// Imprimir cada linha de cartas
	for (int linha = 0; linha < maxAlt; linha++) {
		printf("  ");
		for (int t = 0; t < 7; t++) {
			int alt = alturas[t];
			if (linha < alt) {
				Carta c = j->tab[t].itens[linha];
				print_carta_compacta(c);
			} else {
				printf("    ");
			}
			printf("     ");
		}
		printf("\n|");
	}
	
	printf("\n+================================================================+\n");
	printf("| Legenda: C=Copas | O=Ouros | P=Paus | E=Espadas |               |\n");
	printf("+================================================================+\n\n");
}

// Mapear id do monte para ponteiro de Pilha e tipo
typedef enum { TIPO_INVALIDO=0, TIPO_ESTOQUE, TIPO_DESCARTE, TIPO_FUND, TIPO_TAB } TipoMonte;
typedef struct { Pilha *pilha; TipoMonte tipo; int indice; } RefMonte;

static RefMonte obter_monte(Jogo *j, int id) {
	RefMonte r = {0};
	if (id == 1) { r.pilha = &j->estoque; r.tipo = TIPO_ESTOQUE; r.indice = 0; return r; }
	if (id == 2) { r.pilha = &j->descarte; r.tipo = TIPO_DESCARTE; r.indice = 0; return r; }
	if (id >= 4 && id <= 7) { r.pilha = &j->fund[id - 4]; r.tipo = TIPO_FUND; r.indice = id - 4; return r; }
	if (id >= 21 && id <= 27) { r.pilha = &j->tab[id - 21]; r.tipo = TIPO_TAB; r.indice = id - 21; return r; }
	r.tipo = TIPO_INVALIDO; r.pilha = NULL; r.indice = -1; return r;
}

// Ações especiais do estoque
static void acao_estoque(Jogo *j) {
	if (!pilha_vazia(&j->estoque)) {
		int n = j->viradasPorVez;
		for (int i = 0; i < n && !pilha_vazia(&j->estoque); i++) {
			Carta c; pilha_pop(&j->estoque, &c);
			c.faceUp = true;
			pilha_push(&j->descarte, c);
		}
	} else {
		// reciclar descarte de volta para estoque (verso)
		if (pilha_vazia(&j->descarte)) return; // nada a fazer
		Carta c;
		while (pilha_pop(&j->descarte, &c)) {
			c.faceUp = false;
			pilha_push(&j->estoque, c);
		}
	}
}

// Mover um único cartão
static bool mover_uma_carta(Jogo *j, int origem, int destino) {
	RefMonte ro = obter_monte(j, origem);
	RefMonte rd = obter_monte(j, destino);
	if (ro.tipo == TIPO_INVALIDO || rd.tipo == TIPO_INVALIDO) return false;
	if (pilha_vazia(ro.pilha)) return false;
	Carta c; pilha_top(ro.pilha, &c);

	// Regras de destino
	if (rd.tipo == TIPO_FUND) {
		if (!pode_ir_para_fundacao(rd.pilha, c)) return false;
		pilha_pop(ro.pilha, NULL);
		pilha_push(rd.pilha, c);
		return true;
	}
	if (rd.tipo == TIPO_TAB) {
		if (!pode_empilhar_em_tableau(rd.pilha, c)) return false;
		pilha_pop(ro.pilha, NULL);
		pilha_push(rd.pilha, c);
		return true;
	}
	// Outros destinos não permitidos
	return false;
}

// Mover várias cartas de um tableau para outro tableau
static bool mover_varias_cartas(Jogo *j, int origem, int destino, int qtd) {
	RefMonte ro = obter_monte(j, origem);
	RefMonte rd = obter_monte(j, destino);
	if (ro.tipo != TIPO_TAB || rd.tipo != TIPO_TAB) return false;
	if (!sequencia_valida_para_mover(ro.pilha, qtd)) return false;
	// Carta da base do grupo (será colocada sobre o destino)
	Carta base = ro.pilha->itens[ro.pilha->top - qtd + 1];
	if (!pode_empilhar_em_tableau(rd.pilha, base)) return false;
	// mover mantendo ordem
	Carta buffer[52];
	for (int i = qtd - 1; i >= 0; i--) {
		buffer[i] = ro.pilha->itens[ro.pilha->top - (qtd - 1 - i)];
	}
	// pop qtd
	for (int i = 0; i < qtd; i++) pilha_pop(ro.pilha, NULL);
	// push na mesma ordem
	for (int i = 0; i < qtd; i++) pilha_push(rd.pilha, buffer[i]);
	return true;
}

// Após retirar cartas de um tableau, se o topo estiver com verso, vira-o
static void virar_topo_se_preciso(Pilha *tab) {
	if (!pilha_vazia(tab)) {
		Carta c; pilha_top(tab, &c);
		if (!c.faceUp) { tab->itens[tab->top].faceUp = true; }
	}
}

static bool vitoria(const Jogo *j) {
	for (int i = 0; i < 4; i++) {
		if (pilha_tamanho(&j->fund[i]) != 13) return false;
	}
	return true;
}

// Loop principal
int main(void) {
	srand((unsigned)time(NULL));
	Jogo jogo; memset(&jogo, 0, sizeof(jogo));

	// escolher quantidade de viradas
	int n;
	do {
		printf("Digite a quantidade de cartas para virar do monte 1 por jogada (1 ou 3): ");
		if (scanf("%d", &n) != 1) return 0;
	} while (n != 1 && n != 3);
	jogo.viradasPorVez = n;

	distribuir_inicial(&jogo);

	while (1) {
		desenhar(&jogo);
		if (vitoria(&jogo)) {
			printf("Parabéns! Você completou as fundações (4-7). Fim de jogo.\n");
			break;
		}
		printf("Informe movimento (origem destino quantidade). Ex.: 21 24 3 | Origem 1 para virar/reciclar. 0 0 0 para sair.\n> ");
		int origem, destino, qtd;
		if (scanf("%d %d %d", &origem, &destino, &qtd) != 3) {
			printf("Entrada inválida. Tente novamente.\n");
			// limpar stdin
			int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
			continue;
		}
		if (origem == 0 && destino == 0 && qtd == 0) {
			printf("Saindo...\n");
			break;
		}

		// Origem 1: virar do estoque ou reciclar
		if (origem == 1) {
			acao_estoque(&jogo);
			continue;
		}

		RefMonte ro = obter_monte(&jogo, origem);
		if (ro.tipo == TIPO_INVALIDO) { printf("Origem inválida.\n"); continue; }

		// Ao selecionar tableau com topo de verso, virar carta
		if (ro.tipo == TIPO_TAB && !pilha_vazia(ro.pilha)) {
			Carta cTop; pilha_top(ro.pilha, &cTop);
			if (!cTop.faceUp) {
				ro.pilha->itens[ro.pilha->top].faceUp = true;
				continue; // apenas virar
			}
		}

		RefMonte rd = obter_monte(&jogo, destino);
		if (rd.tipo == TIPO_INVALIDO) { printf("Destino inválido.\n"); continue; }

		// Regras de quantidade implícitas
		if (ro.tipo == TIPO_DESCARTE || ro.tipo == TIPO_FUND) qtd = 1;
		if (rd.tipo == TIPO_FUND) qtd = 1;
		if (ro.tipo == TIPO_FUND && rd.tipo == TIPO_TAB) {
			// permitido mover 1 carta da fundação para tableau
			qtd = 1;
		}

		bool ok = false;
		if (qtd <= 1) {
			ok = mover_uma_carta(&jogo, origem, destino);
			if (ok && ro.tipo == TIPO_TAB) virar_topo_se_preciso(ro.pilha);
		} else {
			ok = mover_varias_cartas(&jogo, origem, destino, qtd);
			if (ok) virar_topo_se_preciso(ro.pilha);
		}

		if (!ok) {
			printf("Movimento inválido pelas regras.\n");
		}
	}

	return 0;
}

