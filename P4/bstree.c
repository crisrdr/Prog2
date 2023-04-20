#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"


#define MAX_BUFFER 64 // Maximum file line size

/* START [_BSTNode] */
typedef struct _BSTNode {
    void * info;
    struct _BSTNode * left;
    struct _BSTNode * right;
    struct _BSTNode * parent;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
    BSTNode * root;
    P_tree_ele_print print_ele;
    P_tree_ele_cmp cmp_ele;
};
/* END [_BSTree] */


/*** BSTNode TAD private functions ***/
BSTNode * _bst_node_new(){
    BSTNode * pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn) {
        return NULL;
    }

    pn->left = pn->right = NULL;
    pn->parent =NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free (BSTNode * pn){
    if (!pn) return;
    if(pn->info)
        free(pn->info);
    free(pn);
}

void _bst_node_free_rec (BSTNode * pn){
    if (!pn) return;

    _bst_node_free_rec(pn->left);
    _bst_node_free_rec(pn->right);
    _bst_node_free(pn);

    return;
}

int _bst_depth_rec (BSTNode * pn) {
    int depthR, depthL;
    if (!pn) return 0;

    depthL = _bst_depth_rec(pn->left);
    depthR = _bst_depth_rec(pn->right);

    if (depthR > depthL) {
        return depthR + 1;
    } else {
        return depthL + 1;
    }
}

int _bst_size_rec(BSTNode * pn) {
    int count = 0;
    if (!pn) return count;

    count += _bst_size_rec(pn->left);
    count += _bst_size_rec(pn->right);

    return count + 1;
}

int _bst_preOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += print_ele(pf, pn->info);
    count += _bst_preOrder_rec(pn->left, pf, print_ele);
    count += _bst_preOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_inOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_inOrder_rec(pn->left, pf, print_ele);
    count += print_ele(pf, pn->info);
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_postOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_postOrder_rec(pn->left, pf, print_ele);
    count += _bst_postOrder_rec(pn->right, pf, print_ele);
    count += print_ele(pf, pn->info);

    return count;
}

BSTNode *_bst_insert_rec (BSTNode *pn, const void *elem, BSTNode *parent, P_tree_ele_cmp cmp_ele){
    int cmp;

    if (!elem || !cmp_ele) return NULL;

    if (!pn){
        pn = _bst_node_new();
        if (!pn) return NULL;
        pn->info = (void*) elem;
        pn->parent = parent;
        return pn;
    }

    cmp = cmp_ele (elem, pn->info);
    if (cmp < 0){
        pn->left = _bst_insert_rec(pn->left, elem, pn, cmp_ele);
    } else if (cmp > 0){
        pn->right = _bst_insert_rec(pn->right, elem, pn, cmp_ele);
    }

    return pn;
}

BSTNode *_bst_find_min_rec(BSTNode *nd){
    BSTNode *auxNode = nd;

    if (!nd) return NULL;

    while (nd->left != NULL){
        if (!auxNode) return NULL;
        auxNode = auxNode->left;
    }
    return auxNode->info;
}


BSTNode *_bst_remove_rec (BSTNode *pn, const void *elem, P_tree_ele_cmp cmp_ele){
    int cmp;
    BSTNode *aux_node = NULL;

    if (!pn || !elem) return NULL;

    cmp = cmp_ele (elem, pn->info);
    if (cmp < 0){
        pn->left = _bst_remove_rec (pn->left, elem, cmp_ele);
    } else if (cmp > 0){
        pn->right = _bst_remove_rec (pn->right, elem, cmp_ele);
    } else {
        if (!pn->left && !pn->right){
            _bst_node_free(pn);
            return NULL;
        } else if (!pn->left){
            aux_node = pn->right;
            _bst_node_free(pn);
            return aux_node;
        } else if (!pn->right){
            aux_node = pn->left;
            _bst_node_free(pn);
            return aux_node;
        } else {
            aux_node = _bst_find_min_rec(pn->right);          
            if (pn->info)
                free(pn->info);  
            pn->info = aux_node->info;
            if (aux_node->right)
                aux_node->parent->left = aux_node->right;
            
            else if (!aux_node->right)
                aux_node->parent->left = NULL;
            
            free(aux_node);   
            return pn;
        }
    }
    
    return pn;
}

/*** BSTree TAD functions ***/
BSTree * tree_init(P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele){
    BSTree * tree = NULL;
    
    if (!print_ele || !cmp_ele) return NULL;

    tree = malloc (sizeof(BSTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;
    tree->print_ele = print_ele;
    tree->cmp_ele = cmp_ele;

    return tree;
}

void tree_destroy (BSTree * tree) {
    if (!tree) return;

    _bst_node_free_rec(tree->root);

    free(tree);
    return;
}

Bool tree_isEmpty( const BSTree * tree){
    if (!tree || !tree->root) return TRUE;
    return FALSE;
}

int tree_depth (const BSTree * tree){
    if (!tree) return -1;

    return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree * tree) {
    if (!tree) return -1;

    return _bst_size_rec(tree->root);
}

int tree_preOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}


/**** TO DO: find_min, find_max, insert, contains, remove ****/

void * tree_find_min (BSTree * tree){
    BSTNode *auxN = NULL;

    if (!tree) return NULL;

    auxN = tree->root;

    while (auxN->left != NULL){
        if (auxN == NULL) return NULL;
        auxN = auxN->left;
    }

    return auxN->info;
}

void * tree_find_max (BSTree * tree){
    BSTNode *auxN = NULL;

    if (!tree) return NULL;

    auxN = tree->root;

    while(auxN->right != NULL){
        if (auxN == NULL) return NULL;
        auxN = auxN->right;
    }

    return auxN->info;
}

Bool tree_contains (BSTree * tree, const void * elem){
    int cmp;
    BSTNode *nd = NULL;

    if (!tree || !elem || tree_isEmpty(tree)) return FALSE;

    nd = tree->root;
    while (nd != NULL){
        cmp = tree->cmp_ele (elem, nd->info);
        if (cmp == 0) return TRUE;
        else if (cmp < 0){
            nd = nd->left;
        } else nd = nd->right;
    }

    return FALSE;
}

Status tree_insert (BSTree * tree, const void * elem){
    BSTNode *nodeAux = NULL;

    if (!tree || !elem) return ERROR;

    nodeAux = _bst_insert_rec(tree->root, elem, NULL, tree->cmp_ele);
    if (!nodeAux) return ERROR;

    tree->root = nodeAux;

    return OK;
}

Status tree_remove (BSTree * tree, const void * elem){

    if (!tree || !elem) return ERROR;

    if (!_bst_remove_rec(tree->root, elem, tree->cmp_ele)) return ERROR;

    return OK;
}