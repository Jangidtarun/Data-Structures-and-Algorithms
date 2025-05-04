from bst import BST_NODE

def main():
    root = BST_NODE(60)

    root.left = BST_NODE(50, parent=root)
    root.right = BST_NODE(70, parent=root)

    root.left.left = BST_NODE(40, parent=root.left)
    root.left.right = BST_NODE(55, parent=root.left)

    root.right.left = BST_NODE(65, parent=root.right)
    root.right.right = BST_NODE(75, parent=root.right)
    
    root.print_tree()
    print(f"smallest node: {root.find_smallest_node().data}")
    print(f"smallest node nr: {root.find_smallest_node_nr().data}")
    print(f"found 55: {root.look_for(55)}")
    print(f"found 55 nr: {root.look_for_nr(55)}")
    print(f"insert 44: {root.insert_node(44)}")
    root.print_tree()
    print(f"insert 74: {root.insert_node(74)}")
    root.print_tree()
    print(f"insert 77: {root.insert_node(77)}")
    root.print_tree()

    print(f"get_node(40): {root.get_node(40)}")

    print(f"delete node(60): {root.delete_node(60)}")
    root.print_tree()


    # bill in preorder traversal
    bill = [
            (1, 60),
            (2, 50),
            (3, 40),
            (4, 44),
            (3, 55),
            (2, 70),
            (3, 65),
            (3, 75),
            (4, 74),
            (4, 76),
            ]

    print_bom(bill)


def print_bom(bill):
    # bill is a dictionary where
    # key = level, value = data

    for level, data in bill:
        for _ in range(level - 1):
            print("   ", end="")
        print(f"{level}. {data}")

if __name__ == "__main__":
    main()
