import math

class Tree:
    def __init__(self, value, left = None, right = None):
        self.value = value
        self.left = left
        self.right = right

    def preorder(self):
        if self.value:
            print(self.value, end=" ")
            if self.left:
                self.left.preorder()
            if self.right:
                self.right.preorder()

    def preorder_stack(self):
        s = [self]
        while s:
            current = s.pop()
            print(current.value, end=" ")
            if current.right:
                s.append(current.right)
            if current.left:
                s.append(current.left)

    def inorder(self):
        if self.value:
            if self.left:
                self.left.inorder()
            print(self.value, end=" ")
            if self.right:
                self.right.inorder()

    def inorder_stack(self):
        s = []
        current = self
        while s or current:
            if current:
                s.append(current)
                current = current.left
            else:
                current = s.pop()
                print(current.value, end=" ")
                current = current.right

    def postorder(self):
        if self.value:
            if self.left:
                self.left.postorder()
            if self.right:
                self.right.postorder()
            print(self.value, end=" ")

    def postorder_stack_1(self):
        s = []
        current = self
        last_vis = None

        while s or current:
            if current:
                s.append(current)
                current = current.left
            else:
                peek = s[-1]
                if peek.right and last_vis != peek.right:
                    current = peek.right
                else:
                    print(peek.value, end=" ")
                    last_vis = s.pop()

    def postorder_stack_2(self):
        s1 = [self]
        s2 = []
        while s1:
            node = s1.pop()
            s2.append(node)
            if node.left:
                s1.append(node.left)
            if node.right:
                s1.append(node.right)
        while s2:
            node = s2.pop()
            print(node.value, end=" ")

    def mirror(self):
        if self is None:
            return

        self.left, self.right = self.right, self.left

        if self.left:
            self.left.mirror()
        if self.right:
            self.right.mirror()

    def bfs(self):
        nodes_queue = [self]
        while nodes_queue:
            current = nodes_queue[0]
            nodes_queue.pop(0)
            print(current.value, end=" ")
            if current.left:
                nodes_queue.append(current.left)
            if current.right:
                nodes_queue.append(current.right)

    def count_nodes(self):
        """
        Solution to problem 32.
        The following algorithm counts the number of nodes in
        a binary tree using preorder dfs.
        """

        num = 0
        if self.value:
            num += 1
            if self.left:
                num += self.left.count_nodes()
            if self.right:
                num += self.right.count_nodes()
        return num

    def height(self):
        h = 0
        if self:
            hl = self.left.height() if self.left else 0
            hr = self.right.height() if self.right else 0
            h = 1 + max(hl, hr)
        return h

    def count_leaves(self):
        """
        Solution to problem 33.
        Count the number of leaf nodes in a binary tree.
        """

        num = 0
        if self.value:
            flag = True
            if self.left:
                num += self.left.count_leaves()
                flag = False
            if self.right:
                num += self.right.count_leaves()
                flag = False
            if flag:
                num += 1
        return num

    def delete_all_leaves(self, is_not_root=False):
        # solution to problem 34.
        # returns the number of nodes deleted

        num = 0
        if self.value:
            flag = True
            if self.left:
                num += self.left.delete_all_leaves(True)
                flag = False
            if self.right:
                num += self.right.delete_all_leaves(True)
                flag = False
            if flag and is_not_root:
                num += 1
                self.value = None
        return num

    def is_complete(self):
        """
        determines whether a binary tree is complete.
        solution to problem 37.

        i think i need to do bfs here.
        """

        q = [self]
        seen_none = False

        while q:
            current = q.pop(0)
            if current:
                if seen_none:
                    return False
                q.append(current.left)
                q.append(current.right)
            else:
                seen_none = True
        return True

    def is_perfect(self):
        """
        solution to problem 36.

        terminology mismatch
        in the book
        perfect tree -> complete tree
        complete tree -> nearly complete tree
        """

        nodes = self.count_nodes()
        height = self.height()

        left_expr = nodes + 1
        righ_expr = 2 ** height

        # print("------------debugging-------------")

        # print(f"nodes: {nodes}")
        # print(f"left_expr: {left_expr}")
        # print(f"righ_expr: {righ_expr}")

        # print("----------end debugging-----------")

        return left_expr == righ_expr

    def __str__(self):
        lines = []
        self._build_str(self, lines, 0)
        return "\n".join(lines)

    def _build_str(self, node, lines, level):
        if node is not None:
            self._build_str(node.right, lines, level + 1)
            lines.append("    " * level + str(node.value))
            self._build_str(node.left, lines, level + 1)


def height_of_tree(n):
    """
    solution to problem 35.
    given the number of nodes in a complete or nearly complete binary tree,
    finds the height of the tree.
    """

    assert n != 0
    return math.floor(math.log(n, 2)) + 1

def logerror(message):
    """
    Just wanted to pring text in some(red) color
    """

    text_color = "\033[31m"
    default_color = "\033[0m"
    print(f"{text_color}{message}{default_color}")

def main():

    tree = Tree(1, Tree(2, Tree(4), Tree(5, Tree(8))), Tree(3, Tree(6), Tree(7, Tree(9))))


    print("pre-order traversal:")
    tree.preorder()

    print("\npre-order traversal using a stack:")
    tree.preorder_stack()

    print("\nin-order traversal:")
    tree.inorder()

    print("\nin-order traversal using a stack:")
    tree.inorder_stack()

    print("\npost-order traversal:")
    tree.postorder()

    print("\npost-order traversal using a stack:")
    tree.postorder_stack_2()

    print("\nbfs traversal:")
    tree.bfs()
    print()

    print(f"number of nodes: {tree.count_nodes()}")
    print(f"number of leaves: {tree.count_leaves()}")
    print(f"is tree complete: {tree.is_complete()}")
    print(f"is tree perfect: {tree.is_perfect()}")
    print(f"height of tree: {tree.height()}")

    print("tree representation:")
    print(tree)

    tree.mirror()
    print(tree)



if __name__ == "__main__":
    main()
