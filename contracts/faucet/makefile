-include ../.env

compile:
	@mkdir -p build
	@cd build && eosio-cpp --abigen -I ../include -R ../ricardian --contract faucet_contract -o faucet.wasm ../src/faucet.cpp
	@cd build && cp faucet.* ..
	@echo "compiled"

deploy:
	cleos -u $(CONTRACT_ENDPOINT) set contract $(CONTRACT_ACCOUNT) ./
	@echo "deployed"
