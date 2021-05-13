from setuptools import setup

setup(
   name='Suite',
   version='0.0.1',
   description='A suite of some numerical stuff.',
   author='Umberto Zerbinati',
   author_email='umberto.zerbinati@kaust.edu.sa',
   packages=['Suite'],  #same as name
   install_requires=['pybind11'], #external packages as dependencies
)
