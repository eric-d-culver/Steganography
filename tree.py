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

def getLeaves(root, leaves):
	if root == None:
		return
	elif root.left != None or root.right != None:
		getLeaves(root.left, leaves)
		getLeaves(root.right, leaves)
	else:
		leaves.append(root)
	return leaves
