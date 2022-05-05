# Faucet Smart Contract

Phoenix Testnet Faucet.

## Build
Next are defined preconditions that are required for building the smart contracts.
### Preconditions
- `eosio.cdt` version `1.8`

### Compiling guide
- Go to this project root
- run `./build.sh`

After the last step is completed, the built smart contracts are stored in the `build/contracts` with their corresponding subfolders. Into each subfolders, there are the respective `.abi` and `.wasm` files.

> For standard building guides, follow the instructions in [Build and deploy](https://developers.eos.io/manuals/eosio.contracts/latest/build-and-deploy) section.

## Useful cleos commands
Next are defined the corresponding cleos commands to interact with the smart contract.

### addfaucet
`cleos push action faucet.libre addfaucet '{"account":"<name>","interval":"<time_point_sec>","max_tokens_per_interval":<uint32>}' -p faucet.libre@active`

You can replace `<time_point_sec>` to `1970-01-01T00:00:30` which is equal to 30 seconds.

### rmfaucet
`cleos push action faucet.libre rmfaucet '{"account":"<name>"}' -p faucet.libre@active`

### givetokens
`cleos push action faucet.libre givetokens '{"faucet":"<name>","to":"<name>"}' -p <faucet>@active`