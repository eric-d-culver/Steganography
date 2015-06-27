
def byteToBits(byte):
	bits = []
	for i in range(8):
		bits.append((byte & (1 << i)) >> i)
	return bits

class bitRead:
	def __init__(self, file):
		self.file = file
		self.bits = []

	def read(self, numBits):
		while len(self.bits) < numBits and (not self.isEOF()):
			nextByte = ord(self.file.read(1))
			self.bits.extend(byteToBits(nextByte))
		value = self.bits[:numBits]
		self.bits = self.bits[numBits:]
		return value

	def peek(self, numBits):
		while len(self.bits) < numBits and (not self.isEOF()):
			nextByte = ord(self.file.read(1))
			self.bits.extend(byteToBits(nextByte))
		value = self.bits[:numBits]
		return value

	def isEOF(self):
		if self.file.read(1) == '':
			return True
		else:
			self.file.seek(-1, 1)
			return False
