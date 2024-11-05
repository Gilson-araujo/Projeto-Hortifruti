#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para usar o system("clear")
#include <locale.h>


// Estrutura para armazenar os produtos
typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    int tipo; // 1 para quilo, 2 para unidade
} Produto;

// Estrutura para armazenar as vendas
typedef struct {
    int idProduto;
    float quantidadeVendida;
    int tipoVenda; // 1 para quilo, 2 para unidade
} Venda;

// Lista de produtos e vendas
Produto produtos[100];
Venda vendas[100];
int numProdutos = 0;
int numVendas = 0;

// Estruturas de login
char admin_user[] = "admin";
char admin_pass[] = "admin123";
char user_user[] = "usuario";
char user_pass[] = "senha123";

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear"); // Para Linux ou Mac
    #endif
}

// Função para esperar o usuário pressionar Enter
void esperarUsuario() {
    printf("\nPressione Enter para continuar...");
    getchar(); // Para capturar o Enter
    getchar(); // Para garantir que o usuário realmente pressione Enter
}

// Função para login
int login() {
    char usuario[50];
    char senha[50];

    limparTela();
    printf("Login: ");
    scanf("%s", usuario);
    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(usuario, admin_user) == 0 && strcmp(senha, admin_pass) == 0) {
        return 1; // Login de admin
    } else if (strcmp(usuario, user_user) == 0 && strcmp(senha, user_pass) == 0) {
        return 2; // Login de usuário comum
    } else {
        printf("Usuário ou senha incorretos!\n");
        esperarUsuario();
        return 0; // Falha no login
    }
}

// Função para cadastrar produtos (apenas admin)
void cadastrarProduto() {
    Produto novoProduto;
    int tipo;

    limparTela();
    printf("ID do produto: ");
    scanf("%d", &novoProduto.id);
    printf("Nome do produto: ");
    scanf("%s", novoProduto.nome);
    printf("Preço do produto (por quilo ou unidade): ");
    scanf("%f", &novoProduto.preco);

    printf("O produto é vendido por:\n");
    printf("1. Quilo\n");
    printf("2. Unidade\n");
    printf("Escolha uma opção: ");
    scanf("%d", &tipo);

    if (tipo == 1) {
        printf("Quantidade disponível (em quilos): ");
        scanf("%d", &novoProduto.quantidade);
    } else if (tipo == 2) {
        printf("Quantidade disponível (em unidades): ");
        scanf("%d", &novoProduto.quantidade);
    } else {
        printf("Opção inválida!\n");
        esperarUsuario();
        return;
    }

    novoProduto.tipo = tipo;
    produtos[numProdutos] = novoProduto;
    numProdutos++;

    printf("Produto cadastrado com sucesso!\n");
    esperarUsuario();
}

// Função para exibir estoque
void exibirEstoque() {
    limparTela();
    printf("\n--- Estoque de Produtos ---\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f | Quantidade: %d %s\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade,
               produtos[i].tipo == 1 ? "quilos" : "unidades");
    }
    esperarUsuario();
}

// Função para registrar uma venda na lista de vendas
void registrarVenda(int idProduto, float quantidadeVendida, int tipoVenda) {
    Venda novaVenda;
    novaVenda.idProduto = idProduto;
    novaVenda.quantidadeVendida = quantidadeVendida;
    novaVenda.tipoVenda = tipoVenda;

    vendas[numVendas] = novaVenda;
    numVendas++;
}

// Função para realizar vendas (usuário comum)
void realizarVenda() {
    int id, quantidade;
    float quantidadeKg;
    
    limparTela();
    printf("ID do produto para venda: ");
    scanf("%d", &id);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            if (produtos[i].tipo == 1) { // Venda por quilo
                printf("Quantidade a ser vendida (em quilos): ");
                scanf("%f", &quantidadeKg);
                
                if (produtos[i].quantidade >= quantidadeKg) {
                    produtos[i].quantidade -= quantidadeKg;
                    registrarVenda(id, quantidadeKg, 1);
                    printf("Venda de %.2f quilos realizada com sucesso!\n", quantidadeKg);
                } else {
                    printf("Quantidade insuficiente em estoque!\n");
                }
            } else if (produtos[i].tipo == 2) { // Venda por unidade
                printf("Quantidade a ser vendida (em unidades): ");
                scanf("%d", &quantidade);

                if (produtos[i].quantidade >= quantidade) {
                    produtos[i].quantidade -= quantidade;
                    registrarVenda(id, (float)quantidade, 2);
                    printf("Venda de %d unidades realizada com sucesso!\n", quantidade);
                } else {
                    printf("Quantidade insuficiente em estoque!\n");
                }
            }
            esperarUsuario();
            return;
        }
    }
    printf("Produto não encontrado!\n");
    esperarUsuario();
}

// Função para consultar produto por nome
void consultarProduto() {
    char nome[50];
    limparTela();
    printf("Nome do produto para consulta: ");
    scanf("%s", nome);

    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("ID: %d | Nome: %s | Preço: %.2f | Quantidade: %d %s\n", 
                   produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade,
                   produtos[i].tipo == 1 ? "quilos" : "unidades");
            esperarUsuario();
            return;
        }
    }
    printf("Produto não encontrado!\n");
    esperarUsuario();
}

// Função para atualizar as informações de um produto
void atualizarProduto() {
    int id, opcao;
    float novoPreco;
    int novaQuantidade;
    char novoNome[50];

    limparTela();
    printf("Digite o ID do produto que deseja atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            printf("Produto encontrado: %s | Preço atual: %.2f | Quantidade: %d\n", 
                   produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
            
            printf("O que deseja atualizar?\n");
            printf("1. Nome\n");
            printf("2. Preço\n");
            printf("3. Quantidade\n");
            printf("4. ID\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", novoNome);
                    strcpy(produtos[i].nome, novoNome);
                    printf("Nome atualizado com sucesso!\n");
                    break;
                case 2:
                    printf("Digite o novo preço: ");
                    scanf("%f", &novoPreco);
                    produtos[i].preco = novoPreco;
                    printf("Preço atualizado com sucesso!\n");
                    break;
                case 3:
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &novaQuantidade);
                    produtos[i].quantidade = novaQuantidade;
                    printf("Quantidade atualizada com sucesso!\n");
                    break;
                case 4:
                    printf("Digite o novo ID: ");
                    scanf("%d", &id);
                    produtos[i].id = id;
                    printf("ID atualizado com sucesso!\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
            }
            esperarUsuario();
            return;
        }
    }

    printf("Produto não encontrado!\n");
    esperarUsuario();
}

// Função para exibir o relatório de vendas
void exibirRelatorioVendas() {
    limparTela();
    printf("\n--- Relatório de Vendas ---\n");
    for (int i = 0; i < numVendas; i++) {
        int idProduto = vendas[i].idProduto;
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].id == idProduto) {
                printf("Produto: %s | Quantidade vendida: %.2f %s\n", 
                       produtos[j].nome, vendas[i].quantidadeVendida,
                       vendas[i].tipoVenda == 1 ? "quilos" : "unidades");
            }
        }
    }
    esperarUsuario();
}

// Menu do administrador
void menuAdmin(int *executando) {
    int opcao;
    do {
        printf("\n--- Menu Administrador ---\n");
        printf("1. Cadastrar produto\n");
        printf("2. Exibir estoque\n");
        printf("3. Exibir relatório de vendas\n");
        printf("4. Atualizar produto\n");
        printf("5. Logout\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        limparTela();
        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                exibirEstoque();
                break;
            case 3:
                exibirRelatorioVendas();
                break;
            case 4:
                atualizarProduto();
                break;
            case 5:
                printf("Fazendo logout...\n");
                esperarUsuario();
                return;
            case 6:
                printf("Saindo do programa...\n");
                *executando = 0; // Sinaliza para sair do programa
                return;
            default:
                printf("Opção inválida!\n");
                esperarUsuario();
        }
    } while (*executando);
}

// Menu do usuário comum
void menuUsuario(int *executando) {
    int opcao;
    do {
        printf("\n--- Menu Usuário ---\n");
        printf("1. Realizar venda\n");
        printf("2. Consultar produto\n");
        printf("3. Exibir estoque\n");
        printf("4. Logout\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        limparTela();
        switch (opcao) {
            case 1:
                realizarVenda();
                break;
            case 2:
                consultarProduto();
                break;
            case 3:
                exibirEstoque();
                break;
            case 4:
                printf("Fazendo logout...\n");
                esperarUsuario();
                return;
            case 5:
                printf("Saindo do programa...\n");
                *executando = 0; // Sinaliza para sair do programa
                return;
            default:
                printf("Opção inválida!\n");
                esperarUsuario();
        }
    } while (*executando);
}

// Função principal
int main() {
    
	setlocale(LC_ALL, "Portuguese");
	
	int role;
    int executando = 1; // Variável de controle de execução

    do {
        role = login();

        if (role == 1) {
            menuAdmin(&executando);
        } else if (role == 2) {
            menuUsuario(&executando);
        }
    } while (executando); // Continua rodando enquanto "executando" for verdadeiro

    printf("Programa encerrado. Até mais!\n");
    return 0;
}