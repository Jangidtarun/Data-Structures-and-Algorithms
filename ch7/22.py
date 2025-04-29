# Chapter 7 Project 22
# Project description
"""
Write a program that reads a list of names and telephone numbers from a
text file and inserts them into a BST tree. Once the tree has been built,
present the user with a menu that allows him or her to search the list for a
specified name, insert a new name, delete an existing name, or print the
entire phone list. At the end of the job, write the data in the list back to the
file. Test your program with at least 10 names
"""

#
# solution steps
# TODO
# 1. import the contacts from a list to a variable
# 2. convert that list into a binary tree
#

import csv

class Node:
    def __init__(self, key, data, parent=None, left=None, right=None):
        self.key = key
        self.data = data
        self.parent = parent
        self.left = left
        self.right = right


    def insert(self, node):
        if self.key < node["key"]:
            # go right
            if self.right:
                self.right.insert(node)
            else:
                self.right = Node(key=node["key"], data=node["data"], parent=self)
        elif self.key > node["key"]:
            # go left
            if self.left:
                self.left.insert(node)
            else:
                self.left = Node(key=node["key"], data=node["data"], parent=self)
        else:
            print("name already exist")


    def list_to_bst(self, seqlist):
        for item in seqlist:
            node = {
                "key": item["name"],
                "data": item["phone"]
            }
            self.insert(node)
            
    def print_tree(self, prefix="", is_left=True):
        # it pretty prints the tree
        # using some unicode branch characters

        if self is not None:
            connector = "├── " if is_left else "└── "
            print(prefix + connector + f"{self.key} {self.data}")

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



def load_contacts(filepath):
    contacts = []
    with open(filepath, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            contacts.append(row)
    return contacts


def user_menu():
    # well well well
    pass
    

def main():
    filepath = "./contacts.txt"
    contacts = load_contacts(filepath)
    print(contacts)

    root = Node(key="root", data="000")
    root.list_to_bst(contacts)
    root.print_tree()


if __name__ == "__main__":
    main()
