#include <stdio.h>
#include <stdlib.h>

typedef char * cstr;

struct node
{
  cstr val;

  struct node * children;
  size_t child_count;
};


struct node create_tree_node(cstr val)
{
  struct node new_node = {
    .val = val
  };
  return new_node;
}


void node_append_child(struct node * parent, struct node new_child)
{
  struct node * old_children = parent->children;
  size_t new_child_count = parent->child_count + 1;

  struct node * new_children = calloc(new_child_count, sizeof(*new_children));

  for (size_t i = 0; i < parent->child_count; i++) {
    new_children[i] = old_children[i];
  }

  if (old_children)
    free(old_children);

  parent->children = new_children;
  parent->child_count = new_child_count;

  parent->children[parent->child_count - 1] = new_child;
}


void print_tree_(struct node tree, int dept)
{
  for (size_t j = 0; j < dept; j++) {
    printf(" ");
  }

  printf("%d: %s\n", dept, tree.val);

  for (size_t i = 0; i < tree.child_count; i++) {
    print_tree_(tree.children[i], dept + 1);
  }
}

void print_tree(struct node tree)
{
  print_tree_(tree, 0);
}


int main()
{
   struct node tree = create_tree_node("Parent");

   struct node child_1 = create_tree_node("Ole");
   struct node child_2 = create_tree_node("Anna");
   struct node child_21 = create_tree_node("Dole");
   struct node child_22 = create_tree_node("Doffen");

   node_append_child(&child_1, child_21);
   node_append_child(&child_1, child_22);
   node_append_child(&tree, child_1);
   node_append_child(&tree, child_2);

   print_tree(tree);

   return 0;
}
