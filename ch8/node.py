# Node class
class Node:
    def __init__(self, data, bal=0, left=None, right=None):
        self.data = data
        self.bal = bal
        self.left = left
        self.right = right

    
    def left_balance(self):
        if self.bal < 0:
            self.rotate_right()
        else:
            self.left.rotate_left()
            self.rotate_right()


    def right_balance(self):
        if self.bal > 0:
            self.rotate_left()
        else:
            self.right.rotate_right()
            self.rotate_left()
    

    def rotate_right(self):
        pass


    def rotate_left(self):
        pass


