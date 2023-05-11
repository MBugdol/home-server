from fastapi import FastAPI, HTTPException, status
import structures as structs
import mainlogic as logic

from backend import FileHandler

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)
	
app = FastAPI()

fh = FileHandler()

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
def login(args: structs.LoginParams):
	print(f"Login: {args.login}, password: {args.password}")

	return {"id" : 0}

@app.post('/upload/init')
def initializeFileTransfer():
	pass