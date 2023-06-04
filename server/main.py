from fastapi import FastAPI, HTTPException, status, Request
import structures as structs
import mainlogic as logic
import functools

from backend import FileHandler
import backend

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)
	
app = FastAPI()

fh = FileHandler()

def exceptionAs422Details(func):
	@functools.wraps(func)
	def exceptionAs422DetailsDecorator(*args, **kwargs):
		try:
			func()
		except Exception as e:
			raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail=str(e))
	return exceptionAs422DetailsDecorator

@app.get('/')
def root():
	return {'message' : 'Hello world!'}

@app.post('/add-folder/')
def add_folder(folder: structs.Folder):
	try:
		fh.createFolder(folder.directory)
	except Exception as e:
		print(e)
		raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail='The given folder path must be absolute with regard to server root directory')
	
@app.post('/login')
def login(user: structs.User):
	if(backend.login(user.login, user.password)):
		return "Login successful!"
	raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail="Invalid login or password")

@app.post('/register', status_code = status.HTTP_201_CREATED)
def register(user: structs.User):
	backend.registerUser(user.login, user.password)
	return "User successfuly registered!"


@app.post('/upload/init')
def initializeFileTransfer():
	pass