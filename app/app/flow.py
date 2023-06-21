from PySide6.QtCore import QObject, Slot, Signal
from typing import Union

class FlowController (QObject):
	pushRequest = Signal(str, 'QVariant')
	switchRequest = Signal(str)
	popRequest = Signal()
	def __init__(self):
		QObject.__init__(self)
	
	@Slot(str, 'QVariant')
	@Slot(str)
	def push(self, obj, args: dict = {}):
		self.pushRequest.emit(obj, args)

	@Slot(str)
	def switchTo(self, obj):
		self.switchRequest.emit(obj)

	@Slot()
	def pop(self):
		self.popRequest.emit()