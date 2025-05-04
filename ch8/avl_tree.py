from node import Node

# AVL Tree class
class AVL_Tree:
    def __init__(self, count=0, root=None):
        self.count = 0
        self.root = root


    def insert(self, newdata):
        if self.root is None:
            self.root = Node(newdata)
            self.count += 1
            return True
        else:
            if newdata < self.root.data:
                self.root.left.insert(newdata)
                if self.root.bal < 0:
                    self.root.left_balance()
                return True
            else:
                self.root.right.insert(newdata)
                if self.root.bal > 0:
                    self.root.right_balance()
                return True
            self.count += 1
        return False


    def delete(self, dltkey):
        if self.root is None:
            return False
        else:
            if dltkey < self.root.data:
                self.left.delete(dltkey)
                if self.root.bal > 0:
                    self.root.delright_balance()
            else:
                self.right.delete(dltkey)
                if self.root.bal < 0:
                    self.root.delleft_balance()
        return True




if __name__ == "__main__":
    pass
