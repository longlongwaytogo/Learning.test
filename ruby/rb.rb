puts "ruby中国"
BEGIN {
 a = 3
 b = 4
 c = a + b
 puts "初始化 Ruby 程序"
 puts c
}
#dsf
# dfs

=begin
这是注释。
这也是注释。
这也是注释。
这还是注释。
=end
END {
	 puts " End"
}

puts 'escape using "\\"';
puts 'that\'s right';

puts "相乘: #{24*60*60}";

name = "Ruby"
puts name;
puts "#{name+",ok"}";
 puts '\32'
 puts '\16'
 ary = [ "fred",10,3.14,"This is a string","last element",]
 ary.each do |i|
	puts i
end

hsh ={ "red" =>0xf00, "green" =>0x0f0, "blue" =>0x00f };
hsh.each do |key,value| 
	print key, "is" ,value, "\n"
	end
	
	(10..15).each do |n|
	print n, " "
	end
	
	puts "----------------------"
	 class Vehicle	 
		 @@no_of_customers=0
		 def setWheelSize(size)
			 puts "size:" 
			 puts size
		 end
    
		# Number horsepower
		# Character type_of_tank
		# Number Capacity
		
		# Function speeding
		# {
		# }
		
		# Function driving
		# {
		
		# }
		
		# Function halting
		# {
		# }
	# }
	 end
	 
	 cust1 = Vehicle.new
	 cust1.setWheelSize(2)
	
	
	# simple class 
	class Customer
	@@no_of_customers = 0;
	def initialize(id,name,addr)
		@cust_id = id
		@cust_addr = addr
		@cust_name = name
	end 
	
	def display_details()
		puts "Customer id #@cust_id"
		puts "Customer name #@cust_name"
		puts "Customer address #@cust_addr"
	end
	
	def total_no_of_customers()
		@@no_of_customers +=1
		puts "Total number of customers: #@@no_of_customers"
	end
    end 
	
	c1 = Customer.new("1","John","Wisdom Apartments,Luyhiya") 
	c2 = Customer.new("2","Poul", "New Empire road,Khandala")
	
	c1.display_details()
	c1.total_no_of_customers();
	
	c2.display_details();
	c2.total_no_of_customers();
	
	
	puts "---------------"
	
	$global_variable = 10;
	class Class1 
		def print_global
			puts "global value Class1 output : #$global_variable" 
		end
	end 
	
	class Class2
		def print_global
			puts "globale value Class2 output:#$global_variable"
		end
	end
	
	classobj1 = Class1.new 
	classobj2 = Class2.new 
	classobj1.print_global
	classobj2.print_global
	
	class Example
		VAR1 = 100
		@var2 = 200
		def show
			puts "one:#{VAR1}"
			puts "two:#@var2"
		end
	end
	
	eg = Example.new
	eg.show()
	
	puts __FILE__
	puts __LINE__
	puts self 
	
	a, b, c = 10, 20, 30
	
	puts a,b,c 
	puts "defind?"
	foo = 42
	puts defined? foo 
	puts defined? $_
	puts defined? bar 