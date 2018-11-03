pragma solidity ^0.4.18;

contract SplitIt {

	address[] employees = [//people here];
	uint totalReceived = 0;
	mapping (address => uint) withdrawnAmounts;

	// constructor for contract
	constructor() public payable {
        updateTotalReceived()
    }

    // fallback function. Whenever someone sends ether.
    function () public payable {
    	updateTotalReceived();
    }

    function updateTotalReceived() internal {
    	totalReceived += msg.value; //msg.value is the amount you're sending
    }

    modifier canWithdraw() {
    	bool contains = false;
    	for (uint i = 0; i < employees.length; i++) {
    		if (employees[i] == msg.sender) {
    			contains = true;
    			// don't break though to avoid unequal gas payment
    		}
    	}
    	require(contains);
    	_; 
    }

    // pays employees fraction of whatever is sitting in acct.
    function withdraw() public canWithdraw {
    	uint amountAllocated = totalReceived/employees.length;
    	uint amountWithdrawn = withdrawnAmounts[msg.sender];
    	uint amount = amountAllocated - amountWithdrawn;
    	withdrawnAmounts[msg.sender] = amountWithdrawn + amount;

    	if (amount > 0) {
    		msg.sender.transfer(amount);
    	}
    }
}