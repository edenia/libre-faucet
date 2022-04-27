#include <faucet.hpp>
#include <eosio/system.hpp>
#include <cmath>

ACTION faucet_contract::addfaucet(name account, eosio::time_point_sec interval, uint32_t max_tokens_per_interval) {
  require_auth(get_self());

  faucet_table _faucet(get_self(), get_self().value);
  auto faucet_itr = _faucet.find(account.value);

  check(faucet_itr == _faucet.end(), "Faucet account is already registered");

  _faucet.emplace(get_self(), [&](auto& row) {
    row.account = account;
    row.interval = interval;
    row.max_tokens_per_interval = max_tokens_per_interval;
  });
}

ACTION faucet_contract::rmfaucet(name account) {
  require_auth(get_self());

  faucet_table _faucet(get_self(), get_self().value);
  auto faucet_itr = _faucet.find(account.value);

  check(faucet_itr != _faucet.end(), "Faucet does not exist");

  _faucet.erase(faucet_itr);
}

ACTION faucet_contract::givetokens(name faucet, name to) {
  require_auth(faucet);

  faucet_table _faucet(get_self(), get_self().value);
  auto faucet_itr = _faucet.find(faucet.value);

  check(faucet_itr != _faucet.end(), "Faucet does not exist");

  uint32_t elapsed = time_point_sec(current_time_point()).sec_since_epoch() - faucet_itr->last_transfer.sec_since_epoch();

  if( elapsed <= faucet_itr->interval.sec_since_epoch() ) {
    check(faucet_itr->max_tokens_per_interval - faucet_itr->transferred_tokens >= TOKENS_PER_REQUEST, "Not so fast...");
  }

  asset amount = asset(TOKENS_PER_REQUEST, symbol(TOKEN_SYMBOL, TOKEN_PRECISION));

  eosio::action(
    permission_level {get_self(), "active"_n},
    "eosio.token"_n,
    "transfer"_n,
    std::make_tuple(get_self(), to, amount, std::string{"Faucet transfer"})
  ).send();

  _faucet.modify( faucet_itr, _self, [&]( auto& row ) {
    if( elapsed > faucet_itr->interval.sec_since_epoch() ) {
        row.transferred_tokens = TOKENS_PER_REQUEST;
    } else {
        row.transferred_tokens = row.transferred_tokens + TOKENS_PER_REQUEST;
    }
    row.last_transfer = time_point_sec(current_time_point());
  });
}