from setuptools import setup, Extension

module = Extension('filter', sources=['filter.c'])

setup(
    name='filter',
    version='1.0',
    description='A module to filter strings based on blacklist',
    ext_modules=[module]
)
