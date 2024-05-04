from setuptools import setup, Extension
import pybind11
import os

cpp_args = ['-std=c++11', '-stdlib=libc++']

sfc_module = Extension(
    'cpp_gym_envs',
    sources=['main.cpp'],
    include_dirs=[pybind11.get_include(), fr'{os.path.dirname(__file__)}\include'],
    language='c++',
    extra_compile_args=cpp_args,
    )

setup(
    name='cpp_gym_envs',
    version='1.0',
    description='Gymnasium environments coded in C++',
    ext_modules=[sfc_module],
)