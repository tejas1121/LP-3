// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

/// @title Bank
/// @notice Simple bank account for customers: deposit, withdraw and show balance.
contract Bank {
    // Balance of each customer (in wei)
    mapping(address => uint256) private balances;

    event Deposited(address indexed customer, uint256 amount, uint256 newBalance);
    event Withdrawn(address indexed customer, uint256 amount, uint256 newBalance);

    // Deposit money: send ETH along with this call (use the Value box in Remix)
    function deposit() public payable {
        require(msg.value > 0, "Deposit amount must be greater than 0");
        balances[msg.sender] += msg.value;
        emit Deposited(msg.sender, msg.value, balances[msg.sender]);
    }

    // Withdraw money: amount is in wei
    function withdraw(uint256 _amount) public {
        require(_amount > 0, "Withdraw amount must be greater than 0");
        require(balances[msg.sender] >= _amount, "Insufficient balance");

        // Update balance first, then send ETH (prevents re-entrancy)
        balances[msg.sender] -= _amount;

        (bool success, ) = payable(msg.sender).call{value: _amount}("");
        require(success, "Transfer failed");

        emit Withdrawn(msg.sender, _amount, balances[msg.sender]);
    }

    // Show balance of the caller (in wei)
    function showBalance() public view returns (uint256) {
        return balances[msg.sender];
    }

    // Show balance of any customer address (in wei)
    function balanceOf(address _customer) public view returns (uint256) {
        return balances[_customer];
    }

    // Total ETH held by the bank contract (in wei)
    function bankTotal() public view returns (uint256) {
        return address(this).balance;
    }
}
