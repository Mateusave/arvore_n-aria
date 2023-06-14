#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó do empregado
struct EmployeeNode {
    char name[50];
    char cargo[50];
    struct EmployeeNode* firstChild;
    struct EmployeeNode* nextSibling;
};

// Função para criar um novo nó do empregado
struct EmployeeNode* createEmployeeNode(char name[], char cargo[]) {
    struct EmployeeNode* newNode = (struct EmployeeNode*)malloc(sizeof(struct EmployeeNode));
    strcpy(newNode->name, name);
    strcpy(newNode->cargo, cargo);
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Função para adicionar um subordinado a um empregado
void addSubordinate(struct EmployeeNode* manager, struct EmployeeNode* subordinate) {
    if (manager->firstChild == NULL) {
        manager->firstChild = subordinate;
    } else {
        struct EmployeeNode* sibling = manager->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = subordinate;
    }
}

// Função para imprimir a organização hierárquica dos empregados
void printOrganization(struct EmployeeNode* employee, int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");  // Espaços para identação
    }
    printf("%s (%s)\n", employee->name, employee->cargo);

    struct EmployeeNode* subordinate = employee->firstChild;
    while (subordinate != NULL) {
        printOrganization(subordinate, level + 1);
        subordinate = subordinate->nextSibling;
    }
}

// Função para buscar um empregado pelo nome na organização hierárquica
struct EmployeeNode* searchEmployee(struct EmployeeNode* employee, char name[]) {
    if (employee == NULL)
        return NULL;
    if (strcmp(employee->name, name) == 0)
        return employee;
    struct EmployeeNode* result = searchEmployee(employee->firstChild, name);
    if (result != NULL)
        return result;
    return searchEmployee(employee->nextSibling, name);
}

int main() {
    struct EmployeeNode* ceo = createEmployeeNode("Mateus", "ceo");

    // Funcionários adicionais
    struct EmployeeNode* manager1 = createEmployeeNode("Otto", "gerente");
    struct EmployeeNode* manager2 = createEmployeeNode("Paula", "gerente");
    struct EmployeeNode* employee1 = createEmployeeNode("Maria", "funcionario");
    struct EmployeeNode* employee2 = createEmployeeNode("Jorge", "funcionario");

    addSubordinate(ceo, manager1);
    addSubordinate(ceo, manager2);
    addSubordinate(manager1, employee1);
    addSubordinate(manager2, employee2);

    printOrganization(ceo, 0);
    int choice = 0;
    while (choice != -1) {
        printf("\nMenu:\n");
        printf("1. Adicionar funcionário\n");
        printf("2. Encerrar o programa\n");
        printf("3. Exibir funcionarios\n");
        printf("Escolha uma opção: ");
        scanf("%d%*c", &choice);

        if (choice == 1) {
            char name[50];
            char cargo[50];
               
            printf("Digite o nome do funcionário: ");
            fgets(name, 50, stdin);
            
            // tirar o \n no final 
            size_t length = strlen(name);
            if (name[length - 1] == '\n') {
                name[length - 1] = '\0';    
            }
            printf("Digite o cargo do funcionario: ");
            fgets(cargo, 50, stdin);
            length = strlen(cargo);
            if (cargo[length - 1] == '\n') {
                cargo[length - 1] = '\0';
            }

            struct EmployeeNode* newEmployee = createEmployeeNode(name, cargo);

            if (ceo == NULL) {
                ceo = newEmployee;
                printf("CEO adicionado com sucesso!\n");
            } else {
                char managerName[50];
                printf("Escolha o gerente (ou superior) para o funcionário (Digite o nome): ");
                fgets(managerName, 50, stdin);
                length = strlen(managerName);
                if (managerName[length - 1] == '\n') {
                    managerName[length - 1] = '\0';
                }

                // Procurar o gerente na organização existente
                struct EmployeeNode* manager = searchEmployee(ceo, managerName);

                if (manager != NULL) {
                    addSubordinate(manager, newEmployee);
                    printf("Funcionário adicionado com sucesso!\n");
                } else {
                    printf("Gerente não encontrado. O funcionário não foi adicionado.\n");
                    free(newEmployee);  // Liberar a memória alocada para o novo funcionário
                }
            }
        } else if (choice == 2) {
            return 0;
        } else if (choice == 3){
            printOrganization(ceo, 0);
        } 
    }

    // Impressão da organização hierárquica dos empregados
    printf("\nOrganização Hierárquica de Empregados:\n");
    if (ceo != NULL) {
        printOrganization(ceo, 0);
    } else {
        printf("Nenhum funcionário adicionado.\n");
    }

    // Impressão da árvore hierárquica de funcionários
    printf("\nÁrvore Hierárquica de Funcionários:\n");
    if (ceo != NULL) {
        printOrganization(ceo, 0);
    } else {
        printf("Nenhum funcionário adicionado.\n");
    }

    return 0;
}