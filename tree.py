class Node(object):
	def __init__(self, data=None, left=None, right=None):
		self.left=left
		self.right=right
		self.data=data

def freeTree(root):
	if root == None:
		return None
	root.left = freeTree(root.left)
	root.right = freeTree(root.right)
	return None
