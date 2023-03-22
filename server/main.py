from fastapi import FastAPI
from pydantic import BaseModel

import backend

print(backend.add(1, 2))


#uvicorn main:app --reload

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)
	
app = FastAPI()

class TestFileRequest(BaseModel):
	filename: str
	isFolder: bool
	testParam: int | None

@app.get("/")
def root():
	return {"Hello":"World"}

@app.post("/test/")
def root(param: TestFileRequest):
	result =  f'Test request of file {param.filename}, which ' + ('is' if param.isFolder else 'isn\'t') + f' a folder'
	if(param.testParam is not None):
		result += f' with a test param of {param.testParam}'
	result += '.'
	return result