# fuzz_toys

fuzz_toys is a collection of small applications for testing fuzzers.

## Requirements

- CMake
- Boost C++ Library

## Building

We use Ubuntu 20.04 for the build environment.

```shell
sudo apt update
sudo apt install -y build-essential cmake libboost-all-dev
mkdir -p build && cd $_
cmake ..
make
```

## Contributing

Please open GitHub Issues and Pull Requests.

## License

fuzz_toys is released under the [MIT License](LICENSE).

## Acknowledgements

This project has received funding from the Acquisition, Technology & Logistics Agency (ATLA) under the National Security Technology Research Promotion Fund 2020 (JPJ004596).
