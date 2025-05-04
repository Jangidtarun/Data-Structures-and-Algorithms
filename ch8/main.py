from avl_tree import AVL_Tree as tree

def main():
    tree_a = tree()

    for i in range(10):
        tree_a.insert(i)

    tree_a.root.preorder()

    

if __name__ == "__main__":
    main()

