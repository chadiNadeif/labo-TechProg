#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

void* allocate(size_t size);

typedef struct {
	void** elements;
	int top;
	size_t max;
} Stack;

Stack stack_init(size_t max_size);
void stack_push(Stack* s, void* element);
void* stack_pop(Stack* s);


/*
* Vous devez definir une noeud que vous appelerez TreeNode. TreeNode va avoir une propriete data lui permettant de recevoir de l'information de different type. 
* TreeNode a aussi deux propriete de type TreeNode nommer left et right.
*/
typedef struct {
	void* data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;


typedef struct Node Node;
typedef struct Node {
	void* data;
	Node* prev;
	Node* next;
	size_t count;
}Queue;

void queue_init(Queue* q);
void queue_push(Queue* q, void* data);
void* queue_pop(Queue* q);

/*
* Programmer l'algorithme de fibonacci. Commencer par faire l'algorithme de base et par la suite ajouter la memoization.
* Faire attention lorsque vous utilisez un type pour une variable qui represente un nombre, int ne depasse pas 2^31-1 ou 2,147,483,647
*/
long long fibonacci(int n) {
	if (n <= 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}

	long long a = 0, b = 1, c;
	for (int i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

/*
* Creer un Noeud, assigner lui la valeur de data, metter c'est reference a NULL et retourner le noeud.
*/
TreeNode* tree_create_node(void* data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newNode == NULL) {
		printf("Erreur d'allocation de mémoire\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/*
* Ajouter le noeud  node dans la propriete left ou right qui est NULL de root. On priorise de gauche a droite. Si right et left son NULL on le met dans left.
* Si jamais aucun des noeuds est NULL, ajouter rien.
*/
void tree_add_node(TreeNode* root, TreeNode* node) {
		if (root == NULL || node == NULL) {
			return; 
		}
		if (root->left == NULL) {
			root->left = node;
		}
		else if (root->right == NULL) {
			root->right = node; 
		}
}

/*
* Programmer l'algorithme de depth first search afin de trouver la cle. Pour programmer cet algorithme, vous avez besoins d'une pile/stack, ca definition est fourni.
*/
int dfs(TreeNode* root, void* key) {
	if (root == NULL) {
		return 0; 
	}
	Stack stack = stack_init(100); 
	stack_push(&stack, root); 
	while (stack.top != -1) { 
		TreeNode* current = (TreeNode*)stack_pop(&stack); 
		if (current->data == key) {
			return 1; 
		}
		if (current->right != NULL) {
			stack_push(&stack, current->right);
		}
		if (current->left != NULL) {
			stack_push(&stack, current->left);
		}
	}

	return 0;
}

/*
* Programmer l'algorithme de breath first search afin de trouver la cle. Pour programmer cet algorithme, vous avez besoins d'une file/queue, ca definition est fourni.
*/
int bfs(TreeNode* root, void* key) {
	if (root == NULL) {
		return 0;
	}
	Queue queue;
	queue_init(&queue);
	queue_push(&queue, root);

	while (queue.count > 0) { 
		TreeNode* current = (TreeNode*)queue_pop(&queue); 

		if (current->data == key) {
			return 1;
		}
		if (current->left != NULL) {
			queue_push(&queue, current->left);
		}
		if (current->right != NULL) {
			queue_push(&queue, current->right);
		}
	}
	return 0;
}