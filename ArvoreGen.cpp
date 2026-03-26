#include <iostream>
#include <string>

using namespace std;

enum parentesco {pai, mae, irmao};

typedef struct pessoa {
    string nome, sobrenome;
    int nascimento;
    struct pessoa* pai;
    struct pessoa* mae;
    struct pessoa* irmaos;

} Pessoa, * PONT;

PONT criaNo() {
    PONT novo = new Pessoa;
    novo->irmaos = NULL;
    novo->mae = NULL;
    novo->pai = NULL;
    cout << "nome: " << endl;
    cin >> novo->nome;
    cin.ignore();
    cout << "sobrenome: " << endl;
    cin >> novo->sobrenome;
    cin.ignore();
    cout << "nascimento: " << endl;
    cin >> novo->nascimento;
    cin.ignore();
    return novo;
}

PONT inicializar() {
    return criaNo();
}

PONT buscarFam(PONT raiz, string nome) {
    if (raiz == NULL) return NULL;
    if (raiz->nome == nome) return raiz;
    PONT next = raiz->pai;
    while (next) {
        PONT resp = buscarFam(next, nome); // busca nos filhos da esquerda
        if (resp) return resp;
        next = next->irmaos;
    }
    next = raiz->mae;
    while (next) {
        PONT resp = buscarFam(next, nome); // busca nos filhos da direita
        if (resp) return resp;
        next = next->irmaos;
    }
    next = raiz->irmaos;
    while (next) {
        PONT resp = buscarFam(next, nome); // busca nos irmaos da raiz principal
        if (resp) return resp;
        next = next->irmaos;
    }
    return NULL; // nao achou 
}

PONT inserirAux(PONT raiz, PONT pessoa, string nome, parentesco pa) {
    if (pa==pai || pa==mae) {
        if (pessoa) return NULL; // se ja  tem pai/mae
        else {
          PONT possivel = buscarFam(raiz,nome); // vai buscar se ja existe em outro lugar da arvore
          if (possivel) return possivel;
        }
    }
    PONT novo = criaNo();
    return novo;
}

bool inserir(PONT raiz, string origin, string nome, parentesco pa) { // 
    PONT origem = buscarFam(raiz,origin);    // busca quem é o pai 
    if (origem == NULL) return false;
    PONT novo;
    if (pa==pai) {
            novo = inserirAux(raiz,origem->pai,nome, pa);
            origem->pai = novo;
            return true;
    } else if (pa==mae) {
            novo = inserirAux(raiz,origem->mae,nome, pa);
            origem->mae = novo;
            return true;
    }
    novo = inserirAux(raiz,origem,nome, pa); // eh irmao
    PONT next = origem->irmaos;
    if (next == NULL) {
        origem->irmaos = novo;
        return true;
        }
    while (next->irmaos) next = next->irmaos;
    next->irmaos = novo;
    return true;
}

void exibirAux(PONT raiz) {
    cout << endl;
    cout << "Nome: " << raiz->nome << endl;
    cout << "Sobrenome: " << raiz->sobrenome << endl;
    cout << "Data de nascimento:" << raiz->nascimento << endl;
    if (raiz->pai) cout << "Pai: " << raiz->pai->nome << endl;
    if (raiz->mae) cout << "Mae: " << raiz->mae->nome << endl;
    cout << endl;
}

void exibir(PONT raiz) {
    if (raiz==NULL) return;
    exibirAux(raiz);
    PONT next = raiz->pai;
    while (next) {
        exibir(next);
        next = next->irmaos;
    }
    next = raiz->mae;
    while (next) {
        exibir(next);
        next = next->irmaos;
    }
    next = raiz->irmaos;
    while (next) {
        exibir(next);
        next = next->irmaos;
    }
}

int main() {
    PONT eu;
    eu = inicializar();
    exibir(eu);
    inserir(eu,"lorenzo","alexandre",pai);
    inserir(eu,"lorenzo","giovana",mae);
    inserir(eu,"lorenzo","isabela",irmao);
    inserir(eu,"giovana","oneide",mae); 
    inserir(eu,"isabela","aline",irmao);
    inserir(eu,"aline","ezequiel",pai); 
    inserir(eu,"isabela","giovana",mae); // parou aqui
    exibir(eu);
    exibir(eu);

};