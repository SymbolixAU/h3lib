#!/bin/bash
repo_url="https://github.com/uber/h3.git"
repo_folder="h3"
compare_folder="src"
repo_src="src/h3lib"

echo "Update from uber/h3? (y/n)"
read -r answer

case $answer in
    [Nn]* ) echo "Quitting..."; exit;;
    [Yy]* ) 
        git clone "$repo_url" "$repo_folder" || { echo "Error cloning repository"; exit 1; }
        mv $repo_folder/$repo_src/include/* $repo_folder/$repo_src/lib
        mv $repo_folder/$repo_src/lib/h3api.h.in $repo_folder/$repo_src/lib/h3api.h
        # Build the init.c

        echo -e "\nDifferences:"
        diff -r --exclude='*.o' "${repo_folder}/${repo_src}/lib" "$compare_folder/"

        echo -e "\nInstall the update? (y/n)"
        read -r answer
        case $answer in
            [Nn]* ) 
                rm -rf $repo_folder
                echo "Removing files and quitting..."; exit;;
            [Yy]* )
                rm -rf $compare_folder
                mkdir $compare_folder
                mv $repo_folder/$repo_src/lib/* $compare_folder/
                rm -rf $repo_folder
                echo "Finished update"
            ;;
            * ) echo "Invalid input";;
        esac
    ;;
    * ) echo "Invalid input";;
esac