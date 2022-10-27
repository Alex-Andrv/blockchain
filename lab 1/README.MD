Просмотреть код контрактов заданного преподавателем проекта, найти место, реализующее определенную логику и привести diff (результат работы git diff), изменяющий поведение смарт-контракта:

- https://github.com/gnosis/MultiSigWallet/blob/master/contracts/MultiSigWallet.sol - сделать, чтобы с баланса multisig-контракта за одну транзакцию не могло бы уйти больше, чем 66 ETH

```solidity
@@ -22,6 +22,7 @@ contract MultiSigWallet {
      *  Constants
      */
     uint constant public MAX_OWNER_COUNT = 50;
+    uint constant public MAX_ETH_VALUE = 66 ether;
 
     /*
      *  Storage
@@ -91,6 +92,11 @@ contract MultiSigWallet {
         _;
     }
 
+    modifier validValue(uint value) {
+        require(value <= MAX_ETH_VALUE);
+        _;
+    }
+
     /// @dev Fallback function allows to deposit ether.
     function()
         payable
@@ -188,6 +194,7 @@ contract MultiSigWallet {
     /// @return Returns transaction ID.
     function submitTransaction(address destination, uint value, bytes data)
         public
+        validValue(value)
         returns (uint transactionId)
     {
         transactionId = addTransaction(destination, value, data);
```
- https://github.com/OpenZeppelin/openzeppelin-contracts/blob/f2112be4d8e2b8798f789b948f2a7625b2350fe7/contracts/token/ERC20/ERC20.sol - сделать, чтобы токен не мог бы быть transferred по субботам
```solidity
  * allowances. See {IERC20-approve}.
  */
 contract ERC20 is Context, IERC20 {
+
+    uint constant public ONE_DAY = 1 days;
+
     mapping (address => uint256) private _balances;
 
     mapping (address => mapping (address => uint256)) private _allowances;
@@ -39,6 +42,11 @@ contract ERC20 is Context, IERC20 {
     string private _name;
     string private _symbol;
 
+    modifier validValue(uint value) {
+        require(value <= MAX_ETH_VALUE);
+        _;
+    }
+
     /**
      * @dev Sets the values for {name} and {symbol}.
      *
@@ -99,6 +107,10 @@ contract ERC20 is Context, IERC20 {
         return _balances[account];
     }
 
+    function isItSaturday() public view returns (uint8) {
+        return ((now / ONE_DAY + 4) % 7) == 5;
+    }
+
     /**
      * @dev See {IERC20-transfer}.
      *
@@ -208,6 +220,7 @@ contract ERC20 is Context, IERC20 {
     function _transfer(address sender, address recipient, uint256 amount) internal virtual {
         require(sender != address(0), "ERC20: transfer from the zero address");
         require(recipient != address(0), "ERC20: transfer to the zero address");
+        require(! isItSaturday(), "Transfers on Saturday are prohibited");
 
         _beforeTokenTransfer(sender, recipient, amount);
```
- https://github.com/mixbytes/solidity/blob/076551041c420b355ebab40c24442ccc7be7a14a/contracts/token/DividendToken.sol - сделать чтобы платеж в ETH принимался только специальной функцией, принимающей помимо ETH еще комментарий к платежу (bytes[32]). Простая отправка ETH в контракт запрещена 
```solidity
@@ -9,9 +9,9 @@
contract DividendToken is StandardToken, Ownable {
@@ -37,7 +37,7 @@ contract DividendToken is StandardToken, Ownable {
}));
}

-    function() external payable {
+    function deposit(bytes[32] comment) external payable {
if (msg.value > 0) {
emit Deposit(msg.sender, msg.value);
m_totalDividends = m_totalDividends.add(msg.value);
@@ -176,3 +176,4 @@ contract DividendToken is StandardToken, Ownable {
uint256 public m_totalHangingDividends;
uint256 public m_totalDividends;
}
+

```