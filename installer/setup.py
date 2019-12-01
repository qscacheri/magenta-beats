from setuptools import find_packages, setup
from package import Package

setup(
    author="Quin Scacheri",
    packages=find_packages(),
    include_package_data=True,
    cmdclass={
        "package": Package
    }
)
