from node import Node

# AVL Tree class
class AVL_Tree:
    def __init__(self, count=0, root=None):
        self.count = 0
        self.root = root


    def insert(self, newdata):
        if self.root is None:
            self.root = Node(newdata)
        else:
            if newdata < self.root.data:
                self.root.left.insert(newdata)
                if self.root.bal < 0:
                    self.root.left_balance()
            else:
                self.root.right.insert(newdata)
                if self.root.bal > 0:
                    self.root.right_balance()
        self.count += 1
        return True



