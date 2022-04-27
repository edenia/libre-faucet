# Faucet Smart Contract

Phoenix Testnet Faucet.

## Prerequisites
- [make](https://www.gnu.org/software/make)
- [eosio](https://developers.eos.io/welcome/latest/getting-started-guide/local-development-environment/index)


## Get started
This repository has a `makefile` to speed up repetitive actions like compiling and deploying.

Before to use the `compile` or `deploy`, copy the `.env.example` into `.env` and replace the example values.

```sh
cp .env.example .env
```

### Compilation
To compile this smart contract, run:
```sh
make compile
```

### Deploy
To deploy this smart contract, run:
```sh
make deploy
```