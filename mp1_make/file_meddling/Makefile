all : fill_file_with_nonsense
	echo "I have mostly created a lot of junk today!"


fill_file_with_nonsense : create_file 
	echo "Hello, there is nothing important here" > silly_file

create_file : 
	touch silly_file

move_file :
	mv silly_file silly_file_new_name

delete_file : 
	rm *_file*

clean : 
	touch junk1 junk2 junk3 junk4 junk5 junk6 junk7

really_clean :
	rm junk*

print_file :
	cat silly_file

