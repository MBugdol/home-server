from fastapi import FastAPI, HTTPException, status, Request, Response
import structures as structs
import functools
import backend

app = FastAPI()

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)

def exceptionAs422Details(func):
	@functools.wraps(func)
	def exceptionAs422DetailsDecorator(*args, **kwargs):
		try:
			func(*args, **kwargs)
		except Exception as e:
			raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail=str(e))
	return exceptionAs422DetailsDecorator

@app.get('/')
def root():
	return {'message' : 'Hello world!'}

@app.post('/init-upload/{path:path}')
@exceptionAs422Details
def upload(path: str | None, file: structs.FileInfo, request: Request, response: Response):
	# get the upload id
	upload_id = backend.initializeFileTransfer(path, file.name, file.size, file.meta.json())
	# append upload_id as a query param to the request url
	location_url = request.url.include_query_params(upload_id = upload_id)
	response.headers["Location"] = str(location_url)

@app.post('/create/{path:path}')
@exceptionAs422Details
def create(path: str, entry: structs.FileInfo):
	print(f"Endpoint createFolder, args: {path}, {entry.json()}")
	backend.create(path, entry.name, entry.meta.json())

@app.post('/create/')
@exceptionAs422Details
def create(entry: structs.FileInfo):
	create(entry, "")
	
