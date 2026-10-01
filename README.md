# psychic-couscous
Instead of making a new repo for all the random scripts or whatever, I'm just going to throw them into here. This will also contain things like the solutions I write for Exercism challenges or other challenge projects.

### Autoblog
Taken from the [blog post announcing this script](https://pshef.work/posts/a-new-script/):

```
Two notes that I want to draw attention to in the script:

1) I have predefined in my dotfile the variable $GITHUB to be the local directory that all of my GitHub repos are cloned to (in my case, it’s ~/GitHub_repos). If you want to try and run this script yourself, you can either set the variable yourself for how your own computer is set up, or you can edit the script so it’s a static path.

2) This script also uses the deploy script that I have saved in my blog repo. While this works for now, because I don’t plan on changing that script any time soon, I may end up removing it and incorporating the script directly into this one so there won’t be any dependencies for this script to work. While I’m thinking about it, I like the idea of repurposing the deploy script to be one I can use for all my GitHub repos, but I’ll have to figure out how to do that at a different time.
```

### C projects
I've been working on learning bare metal C using two different books, but both of those are working with ST microcontrollers. All of the examples I found with ESP32's were either utilizing the arduino IDE or using a bunch of libraries, neither of which accomplished the goal I was setting out to try. After a lot of trial and error (and no AI!) I figured it out. I'm sharing this blink file in case someone else is trying to learn the same thing.

I do want to note, when I flashed this to the microcontroller the terminal does display some watchdog errors but I haven't figured any of that stuff out yet. I'm also sure there are better ways to delay the blinks but...
