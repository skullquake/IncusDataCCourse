{
	var Node=require('./node.js?container');//fake copy for inheritance
	var container=Node;
	container.prototype.src='./scr/mod/wid/container.js';
	container.prototype.nodename='div';
	module.exports=container;
}
