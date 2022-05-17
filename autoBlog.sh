#! /bin/bash

# This script is to help facilitate the ease of writing new blog posts and publishing them on my blog, https://pshef.work. The repos for the website are hosted at https://github.com/pshef.

# This has the variable $GITHUB set in my personal dotfile to be the directory where all of my GitHub repos are cloned to, so if you try to run a version of this on your own system you'll need to make sure this is set first.

# Set variable of PWD
startingDirectory=$(pwd)

# Change to blog directory
cd $GITHUB/blog/pshef

echo -e "Is this a logfile dump? (y/n)"
read logfileConfirm

if [ "$logfileConfirm" == y ]; then
	echo -e "What week number is this?"
	read weekNumber

	echo -e "What year is this?"
	read yearNumber

# Creating logfile blog post
	hugo new posts/Logfile_dump_week"$weekNumber""$yearNumber".md
	cd content/posts

# Writing the logfile blog post
	nvim Logfile_dump_week"$weekNumber""$yearNumber".md

# Running deploy script for updating the blog. See https://raw.githubusercontent.com/pshef/blog/main/pshef/deploy.sh for a copy of this script
	cd $GITHUB/blog/pshef
	./deploy.sh

# Go back to starting working directory
        cd $startingDirectory

# Creating blog post
else
	echo -e "What do you want the blog post to be titled?"
	read blogTitle

	hugo new posts/"$blogTitle".md
	cd content/posts

# Writing the blog post
	nvim "$blogTitle".md

# Running deploy script for updating the blog. See https://raw.githubusercontent.com/pshef/blog/main/pshef/deploy.sh for a copy of this script
        cd $GITHUB/blog/pshef
	./deploy.sh

# Go back to starting working directory
        cd $startingDirectory
fi

# I may end up depreciating the deploy script in favor of incorporating it into this script so everything is all in one place

# Shoutout to @GrahamHelton3 on twitter for the idea!
