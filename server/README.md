# Usage

## Prerequisites
1. Create a virtual Python environment. This is recomended to not clutter the global python environment with local instalations. For a tutorial on python's virtual environments please refer to [this page](https://docs.python.org/3/library/venv.html).
2. Launch the virtual environment
3. Install the required modules:
```Python REPL
pip install -r requirements.txt
```

## Launching the application
1. Launch the server as such:
```Python REPL
uvicorn main:app --reload
```
2. You are all set!