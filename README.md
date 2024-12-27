# Galactic Plane Map

Mapping dust extinction in the Galactic Plane

## Getting Started

These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes. See the deployment section for notes on how to deploy the project on a live system.

### Prerequisites

You will need the following software installed on your system:

- g++
- make
- MPI (Message Passing Interface)

### Installing

Follow these steps to set up the development environment:

1. **Clone the repository:**

   ```sh
   git clone https://github.com/your/repository.git
   cd repository
   ```

2. **Build the project:**

   ```sh
   make
   ```

3. **Run the project:**

   ```sh
   ./run.sh
   ```

### Running the tests

To run the automated tests for this system, follow these steps:

1. **Build the test binaries:**

   ```sh
   make test
   ```

2. **Run the tests:**

   ```sh
   ./bin/test_binary
   ```

### Coding style tests

To ensure code quality and consistency, run the following:

```sh
make lint
```

## Deployment

To deploy this project on a live system, follow these steps:

1. **Build the project:**

   ```sh
   make
   ```

2. **Run the project using MPI:**

   ```sh
   mpirun -np <number_of_processes> ./bin/a.out
   ```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
