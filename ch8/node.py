# Node class
class Node:
    LH = -1
    EH =  0
    RH = +1

    def __init__(self, data, count=0, bal=0, left=None, right=None):
        self.count = count
        self.data = data
        self.bal = bal
        self.left = left
        self.right = right


    def insert(self, newdata, taller):
        if self is None:
            self = Node(newdata)
            taller = True
        else:
            if newdata < self.data:
                self.left.insert(newdata, taller)
                if taller:
                    if root.bal == LH:
                        # was left high
                        # rotate
                        self.ins_left_bal(taller)
                    elif self.bal == EH:
                        # was balance
                        # now left high
                        self.bal = LH
                    elif self.bal == RH:
                        # was right high
                        # now balanced
                        self.bal == EH
                        taller = False
            else:
                self.right.insert(newdata, taller)
                if taller:
                    if self.bal == LH:
                        # was lef high
                        # now balanced
                        self.bal = EH
                        taller = False
                    elif self.bal == EH:
                        # was balanced
                        # now right high
                        self.bal = RH
                    elif self.bal == RH:
                        # was right high
                        # rotate
                        self.ins_right_bal(taller)










if __name__ == "__main__":
    pass
