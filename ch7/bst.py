# This file is an ADT for the bst node

class BST_NODE:
    def __init__(self, data, weight=1, parent=None, left=None, right=None):
        self.data = data
        self.parent = parent
        self.left = left
        self.right = right


    def find_smallest_node(self):
        # finds the smallest node
        # return the whole node and not the node data

        if self.left:
            return self.left.find_smallest_node()
        return self


    def find_smallest_node_nr(self):
        # non recursive version of the find_smallest_node function
        
        current = self
        while current:
            if current.left:
                current = current.left
            else:
                break
        return current


    def find_largest_node(self):
        # finds the largest node
        # returns the whole node and not the node data

        if self.right:
            return self.right.find_largest_node()
        return self


    def find_largest_node_nr(self):
        # non recursive version of the find_largest_node function

        current = self
        while current:
            if current.right:
                current = current.right
            else:
                break
        return current


    def look_for(self, target):
        # performs binary search for target
        # if found returns True else False

        if self.data == target:
            return True
        else:
            if target < self.data:
                if self.left:
                    return self.left.look_for(target)
                else:
                    return False
            elif target > self.data:
                if self.right:
                    return self.right.look_for(target)
                else:
                    return False
        return False


    def look_for_nr(self, target):
        # non recursive version of the look_for function

        current = self
        while current:
            if current.data == target:
                return True
            else:
                if target < current.data:
                    current = current.left
                elif target > current.data:
                    current = current.right
                else:
                    break
        return False


    def get_node(self, data):
        # performs binary search for data
        # return the node if found

        if self.data == data:
            return self
        else:
            if data < self.data:
                if self.left:
                    return self.left.get_node(data)
                else:
                    return None
            elif data > self.data:
                if self.right:
                    return self.right.get_node(data)
                else:
                    return None
        return None

            
    def insert_node(self, data):
        # inserts a node
        # it's always possible to insert a node in a bst
        # so the function always returns True
        # except it already contains that node
        # duplicate nodes are not premitted at the moment

        if self:
            if self.data == data:
                print("Error: Duplicate nodes are not allowed")
                return False
            else:
                if data < self.data:
                    if self.left:
                        return self.left.insert_node(data)
                    else:
                        self.left = BST_NODE(data, parent=self)
                elif data > self.data:
                    if self.right:
                        return self.right.insert_node(data)
                    else:
                        self.right = BST_NODE(data, parent=self)
        else:
            self = BST_NODE(data)
        return True 


    def get_successor(self):
        """
        if self.right is not None:
        return nodes from the right branch in inorder traversal
        """

        # it is already checked at this point that self.right is not None
        return self.right.find_smallest_node()


    def delete_node(self, data):
        # deletes a node

        # get the node with that value
        target_node = self.get_node(data)

        if target_node is None:
            print("Error: Node does not exist")
            return False

        # case 1: No childrent
        # target_node is a leaf node
        if not target_node.left and not target_node.right:
            if target_node.parent:
                # intermediate node
                if target_node.parent.left == target_node:
                    target_node.parent.left = None
                else:
                    target_node.parent.right = None
            else:
                # root node
                target_node.data = None

        # case 2: Only right child
        elif not target_node.left:
            if target_node.parent:
                # intermediate node
                if target_node.parent.left == target_node:
                    target_node.parent.left = target_node.right
                else:
                    target_node.parent.right = target_node.right
            else:
                # root node
                target_node.data = target_node.right.data
                target_node.left = target_node.right.left
                target_node.right = target_node.right.right

        # case 3: Only left child
        elif not target_node.right:
            if target_node.parent:
                # intermediate node
                if target_node.parent.left == target_node:
                    target_node.parent.left = target_node.left
                else:
                    target_node.parent.right = target_node.left
            else:
                # root node
                target_node.data = target_node.left.data
                target_node.left = target_node.left.left
                target_node.right = target_node.left.left

        # case 4: Two children
        else:
            successor = target_node.right.find_smallest_node()
            target_node.data = successor.data

            # delete the successor
            if successor.parent.left == successor:
                successor.parent.left = successor.right
            else:
                successor.parent.right = successor.right

        return True
            

    def print_tree(self, prefix="", is_left=True):
        # it pretty prints the tree
        # using some unicode branch characters

        if self is not None:
            connector = "├── " if is_left else "└── "
            print(prefix + connector + str(self.data))

            # Prepare prefix for children
            if is_left:
                new_prefix = prefix + "│   "
            else:
                new_prefix = prefix + "    "

            # IMPORTANT: first left then right
            if self.left or self.right:
                if self.left:
                    self.left.print_tree(new_prefix, True if self.right else False)
                if self.right:
                    self.right.print_tree(new_prefix, False)




        
       
if __name__ == "__main__":
    pass
