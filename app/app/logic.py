import requests
from PySide6.QtCore import QObject, Slot

_default_url = 'http://localhost:8000'

class RequestsObject (QObject):
	def __init__(self):
		QObject.__init__(self)
		pass

	@Slot(result = str)
	def getRoot(self):
		return str(root())

	@Slot(result = str)
	def postTestEndpoint(self):
		return str(testEndpoint())

def root():
	response = requests.get(_default_url + '/')
	return response.json()

def testEndpoint():
	payload = {
		"filename" : "test.txt",
		"isFolder": False,
		"testParam": None
	}
	response = requests.post(_default_url + '/test/', json = payload)
	return response.json()