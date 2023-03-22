from PySide6.QtCore import QObject, Slot, Signal

class FlowController (QObject):
	pushRequest = Signal(str)
	switchRequest = Signal(str)
	popRequest = Signal()
	def __init__(self):
		QObject.__init__(self)
	
	@Slot(str)
	def push(self, obj):
		self.pushRequest.emit(obj)

	@Slot(str)
	def switchTo(self, obj):
		self.switchRequest.emit(obj)

	@Slot()
	def pop(self):
		self.popRequest.emit()