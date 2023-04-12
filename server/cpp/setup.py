from setuptools import setup
import os 
import sys

library_binary_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'bin')

if not os.path.exists(library_binary_dir):
	sys.exit()

library_binary_file = ""
for content in os.listdir(library_binary_dir):
	if content.endswith('.pyd'):
		library_binary_file = os.path.join('bin', content)
		break

setup(
	name = 'backend',
	version = 0.1,
	data_files=[('', [library_binary_file])]
)

