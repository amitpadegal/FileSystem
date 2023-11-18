#include <stdio.h>
#include "fs.h"
#include <string.h>

int main()
{
    FILE_SYSTEM fs;
    initializeFS(&fs); // 1
    printf("-----------Bootup Successful-----------\n");
    createDir(&fs.tobj, "bin", 0755);
    fs.tobj.current_dir = fs.tobj.root;
    createDir(&fs.tobj, "usr", 0755);
    char user_name[20];
    char password[20];
    printf("Enter Username\n");
    scanf("%s", user_name);
    fflush(stdin);
    printf("Enter password\n");
    scanf("%s", password);
    changeCurrentDir(&fs.tobj, "/usr"); // 14
    createDir(&fs.tobj, user_name, 0755); // 6 
    createDir(&fs.tobj, "/usr/PES", 0755); 
    createDir(&fs.tobj,"/usr/DEL",0755);
    changeCurrentDir(&fs.tobj, "/usr/PES");
    displayFileSystem(&fs.tobj); // 15
    createFile(&fs, "test.txt", 0777); // 2
    displayFileSystem(&fs.tobj);
    writeFile(&fs, "test.txt", "Hello World"); // 4
    readFile(&fs, "test.txt"); // 3
    changeCurrentDir(&fs.tobj, "/usr");
    createFile(&fs, "text.txt", 0777);
    displayFileSystem(&fs.tobj);
    char text[] = "A two-inch layer of freshly fallen snow covered the yard. Stacey peeked outside. To most, it would have been a beautiful sight worthy of taking a photo to put on Instagram. For Stacey, it meant something different. The first snow of the year brought back the witches as the fairies in the yard had to seek shelter to avoid the cold. It was the best compliment that he'd ever received although the person who gave it likely never knew. It had been an off-hand observation on his ability to hold a conversation and actually add pertinent information to it on practically any topic. Although he hadn't consciously strived to be able to do so, he'd started to voraciously read the news when he couldn't keep up on topics his friends discussed because their conversations went above his head. The fact that someone had noticed enough to compliment him that he could talk intelligently about many topics meant that he had succeeded in his quest to be better informed.It had been a late night. To be more correct, it had been an early morning. It was now 3:00 AM and George was just getting home. He wasn't sure if it had been worth it. He was supposed to have been finished by 10:00 PM, but his boss had implored him to stay and help when it was clear they weren't going to meet the 10:00 PM target time. So, he had stayed an extra 5 hours and lost a good night's sleep for something he didn't really believe in, but he did anyway because he was afraid if he refused he might lose his job.It was always the Monday mornings. It never seemed to happen on Tuesday morning, Wednesday morning, or any other morning during the week. But it happened every Monday morning like clockwork. He mentally prepared himself to once again deal with what was about to happen, but this time he also placed a knife in his pocket just in case.Debbie put her hand into the hole, sliding her hand down as far as her arm could reach. She wiggled her fingers hoping to touch something, but all she felt was air. She shifted the weight of her body to try and reach an inch or two more down the hole. Her fingers still touched nothing but air.There was something beautiful in his hate. It wasn't the hate itself as it was a disgusting display of racism and intolerance. It was what propelled the hate and the fact that although he had this hate, he didn't understand where it came from. It was at that moment that she realized that there was hope in changing him.There was no ring on his finger. That was a good sign although far from proof that he was available. Still, it was much better than if he had been wearing a wedding ring on his hand. She glanced at his hand a bit more intently to see if there were any tan lines where a ring may have been, and he's simply taken it off. She couldn't detect any which was also a good sign and a relief. The next step would be to get access to his wallet to see if there were any family photos in it.The alarm went off and Jake rose awake. Rising early had become a daily ritual, one that he could not fully explain. From the outside, it was a wonder that he was able to get up so early each morning for someone who had absolutely no plans to be productive during the entire day.I'm meant to be writing at this moment. What I mean is, I'm meant to be writing something else at this moment. The document I'm meant to be writing is, of course, open in another program on my computer and is patiently awaiting my attention. Yet here I am plonking down senseless sentiments in this paragraph because it's easier to do than to work on anything particularly meaningful. I am grateful for the distraction.The box sat on the desk next to the computer. It had arrived earlier in the day and business had interrupted her opening it earlier. She didnt who had sent it and briefly wondered who it might have been. As she began to unwrap it, she had no idea that opening it would completely change her life.Puppies are soft, cute, funny, and make a big mess. Every month or two our family fosters 6-12 week old puppies for a puppy rescue nonprofit organization. We all enjoy cuddling their furry bodies after a clean bath. Fresh puppy smell is great. The puppies play with each other and our adult dog. They look so funny when they lay on top of each other and sleep. While puppies can be great fun, they also can make big messes. 4-6 puppies can make a lot of puppy pee and poop. Its a challenge to keep the puppies and the puppy pen clean.There were a variety of ways to win the game. James had played it long enough to know most of them and he could see what his opponent was trying to do. There was a simple counterattack that James could use and the game should be his. He began deploying it with the confidence of a veteran player who had been in this situation a thousand times in the past. So, it was with great surprise when his opponent used a move he had never before seen or anticipated to easily defeat him in the game.Twenty-five years Dana had been waiting. She tried to be patient during that time but she hadn't always managed to be as patient as she'd like. But today the opportunity had finally come. The thing she always imagined would make her the happiest person in the world was about to happen. She didnt know why at this specific time she all of a sudden felt sick inside.Should he write it down? That was the question running through his mind. He couldn't believe what had just happened and he knew nobody else would believe him as well. Even if he documented what had happened by writing it down, he still didn't believe anyone would still believe it. So the question remained. Was it be worth it to actually write it down?Do Not Enter. The sign made it clear that they didn't want anyone around. That wasn't going to stop Jack. Jack always lived with the notion that signs were mere suggestions, not actually absolute rules. Thats why the moment Jack looked at the Do Not Enter sign, he walked past it and onto their property.Don't forget that gifts often come with costs that go beyond their purchase price. When you purchase a child the latest smartphone, you're also committing to a monthly phone bill. When you purchase the latest gaming system, you're likely not going to be satisfied with the games that come with it for long and want to purchase new titles to play. When you buy gifts it's important to remember that some come with additional costs down the road that can be much more expensive than the initial gift itself.What is the best way to get what you want? she asked. He looked down at the ground knowing that she wouldnt like his answer. He hesitated, knowing that the truth would only hurt. How was he going to tell her that the best way for him to get what he wanted was to leave her?It went through such rapid contortions that the little bear was forced to change his hold on it so many times he became confused in the darkness, and could not, for the life of him, tell whether he held the sheep right side up, or upside down. But that point was decided for him a moment later by the animal itself, who, with a sudden twist, jabbed its horns so hard into his lowest ribs that he gave a grunt of anger and disgust.Why do Americans have so many different types of towels? We have beach towels, hand towels, bath towels, dish towels, camping towels, quick-dry towels, and let's not forget paper towels. Would 1 type of towel work for each of these things? Let's take a beach towel. It can be used to dry your hands and body with no difficulty. A beach towel could be used to dry dishes. Just think how many dishes you could dry with one beach towel. Ive used a beach towel with no adverse effects while camping. If you buy a thin beach towel it can dry quickly too. I'd probably cut up a beach towel to wipe down counters or for cleaning other items, but a full beach towel could be used too. Is having so many types of towels an extravagant luxury that Americans enjoy or is it necessary? I'd say its overkill and we could cut down on the many types of towels that manufacturers deem necessary.So, what do you think? he asked nervously. He wanted to know the answer, but at the same time, he didn't. He'd put his heart and soul into the project and he wasn't sure he'd be able to recover if they didnt like what he produced. The silence from the others in the room seemed to last a lifetime even though it had only been a moment since he asked the question. So, what do you think? he asked again.Since they are still preserved in the rocks for us to see, they must have been formed quite recently, that is, geologically speaking. What can explain these striations and their common orientation? Did you ever hear about the Great Ice Age or the Pleistocene Epoch? Less than one million years ago, in fact, some 12,000 years ago, an ice sheet many thousands of feet thick rode over Burke Mountain in a southeastward direction. The many boulders frozen to the underside of the ice sheet tended to scratch the rocks over which they rode. The scratches or striations seen in the park rocks were caused by these attached boulders. The ice sheet also plucked and rounded Burke Mountain into the shape it possesses today.There was only one way to do things in the Statton house. That one way was to do exactly what the father, Charlie, demanded. He made the decisions and everyone else followed without question. That was until today.The water rush down the wash and into the slot canyon below. Two hikers had started the day to sunny weather without a cloud in the sky, but they hadnt thought to check the weather north of the canyon. Huge thunderstorms had brought a deluge o rain and produced flash floods heading their way. The two hikers had no idea what was coming.It really doesn't matter what she thinks as it isn't her problem to solve. That's what he kept trying to convince himself. She was trying to insert her opinion where it wasn't wanted or welcome. He already had a plan and even though that plan didn't correspond with what she wanted him to do or what should be done, it wasn't her decision to make. The question now became whether he would stick to his convictions and go through with his plan knowing she wouldnt approve.He had done everything right. There had been no mistakes throughout the entire process. It had been perfection and he knew it without a doubt, but the results still stared back at him with the fact that he had lost.I haven't bailed on writing. Look, I'm generating a random paragraph at this very moment in an attempt to get my writing back on track. I am making an effort. I will start writing consistently again!The leather jacked showed the scars of being his favorite for years. It wore those scars with pride, feeling that they enhanced his presence rather than diminishing it. The scars gave it character and had not overwhelmed to the point that it had become ratty. The jacket was in its prime and it knew it.The trees, therefore, must be such old and primitive techniques that they thought nothing of them, deeming them so inconsequential that even savages like us would know of them and not be suspicious. At that, they probably didnt have too much time after they detected us orbiting and intending to land. And if that were true, there could be only one place where their civilization was hidden.The headphones were on. They had been utilized on purpose. She could hear her mom yelling in the background, but couldn't make out exactly what the yelling was about. That was exactly why she had put them on. She knew her mom would enter her room at any minute, and she could pretend that she hadn't heard any of the previous yelling.It had been a rough day. Things hadn't gone as planned and that meant Hannah got yelled at by her boss. It didn't even matter that it wasn't her fault. When things went wrong at work, Hannah got the blame no matter the actual circumstances. It wasn't fair, but there was little she could do without risking her job, and she wasnt in a position to do that with the plans she had.Nobody really understood Kevin. It wasn't that he was super strange or difficult. It was more that there wasn't enough there that anyone wanted to take the time to understand him. This was a shame as Kevin had many of the answers to the important questions most people who knew him had. It was even more of a shame that theyd refuse to listen even if Kevin offered to give them the answers. So, Kevin remained silent, misunderstood, and kept those important answers to life to himself.Sleeping in his car was never the plan but sometimes things don't work out as planned. This had been his life for the last three months and he was just beginning to get used to it. He didn't actually enjoy it, but he had accepted it and come to terms with it. Or at least he thought he had. All that changed when he put the key into the ignition, turned it and the engine didnt make a sound.It was that terrifying feeling you have as you tightly hold the covers over you with the knowledge that there is something hiding under your bed. You want to look, but you don't at the same time. You're frozen with fear and unable to act. That's where she found herself and she didn't know what to do nextDon't be scared. The things out there that are unknown aren't scary in themselves. They are just unknown at the moment. Take the time to know them before you list them as scary. Then the world will be a much less scary place for you.Hopes and dreams were dashed that day. It should have been expected, but it still came as a shock. The warning signs had been ignored in favor of the possibility, however remote, that it could actually happen. That possibility had grown from hope to an undeniable belief it must be destiny. That was until it wasnt and the hopes and dreams came crashing down.Frank knew there was a correct time and place to reveal his secret and this wasn't it. The issue was that the secret might be revealed despite his best attempt to keep it from coming out. At this point, it was out of his control and completely dependant on those around him who also knew the secret. They wouldn't purposely reveal it, or at least he believed that, but they could easily inadvertently expose it. It was going to be a long hour as he nervously eyed everyone around the table hoping they would keep their mouths shut.Dave wasn't exactly sure how he had ended up in this predicament. He ran through all the events that had lead to this current situation and it still didn't make sense. He wanted to spend some time to try and make sense of it all, but he had higher priorities at the moment. The first was how to get out of his current situation of being naked in a tree with snow falling all around and no way for him to get down.The river slowly meandered through the open space. It had hidden secrets that it didn't want to reveal. It had a well-planned strategy to appear calm, inviting, and appealing. That's how the river lured her unknowing victims to her waters edge.Sometimes it just doesn't make sense. The man walking down the street in a banana suit. The llama standing in the middle of the road. The fairies dancing in front of the car window. The fact that all of this was actually happening and wasn't a dream.Debbie had taken George for granted for more than fifteen years now. He wasnt sure what exactly had made him choose this time and place to address the issue, but he decided that now was the time. He looked straight into her eyes and just as she was about to speak, turned away and walked out the door.It's an unfortunate reality that we don't teach people how to make money (beyond getting a 9 to 5 job) as part of our education system. The truth is there are a lot of different, legitimate ways to make money. That doesn't mean they are easy and that you won't have to work hard to succeed, but it does mean that if you're willing to open your mind a bit you don't have to be stuck in an office from 9 to 5 for the next fifty years o your life.He had disappointed himself more than anyone else. That wasn't to say that he hadn't disappointed others. The fact was that he had disappointed a lot of people who were close to him. The fact that they were disappointed in him was something that made him even more disappointed in himself. Yet here he was, about to do the exact same things that had caused all the disappointment in the first place because he didnt know what else to do.Bryan had made peace with himself and felt comfortable with the choices he made. This had made all the difference in the world. Being alone no longer bothered him and this was essential since there was a good chance he might spend the rest of his life alone in a cell.It's always good to bring a slower friend with you on a hike. If you happen to come across bears, the whole group doesn't have to worry. Only the slowest in the group do. That was the lesson they were about to learn that day.He hid under the covers hoping that nobody would notice him there. It really didnt make much sense since it would be obvious to anyone who walked into the room there was someone hiding there, but he still held out hope. He heard footsteps coming down the hall and stop in front in front of the bedroom door. He heard the squeak of the door hinges and someone opened the bedroom door. He held his breath waiting for whoever was about to discover him, but they never did.Begin today! Thats all the note said. There was no indication from where it came or who may have written it. Had it been meant for someone else? Meghan looked around the room, but nobody made eye contact back. For a brief moment, she thought it might be a message for her to follow her dreams, but ultimately decided it was easier to ignore it as she crumpled it up and threw it away.Finding the red rose in the mailbox was a pleasant surprise for Sarah. She didn't have a boyfriend or know of anyone who was interested in her as anything more than a friend. There wasn't even a note attached to it. Although it was a complete mystery, it still made her heart jump and race a little more than usual. She wished that she could simply accept the gesture and be content knowing someone had given it to her, but that wasnt the way Sarah did things. Now it was time to do a little detective work and try to figure who had actually left the red rose.Twenty-five stars were neatly placed on the piece of paper. There was room for five more stars but they would be difficult ones to earn. It had taken years to earn the first twenty-five, and they were considered the easy ones.She had come to the conclusion that you could tell a lot about a person by their ears. The way they stuck out and the size of the earlobes could give you wonderful insights into the person. Of course, she couldn't scientifically prove any of this, but that didn't matter to her. Before anything else, she would size up the ears of the person she was talking to.He wondered if he should disclose the truth to his friends. It would be a risky move. Yes, the truth would make things a lot easier if they all stayed on the same page, but the truth might fracture the group leaving everything in even more of a mess than it was not telling the truth. It was time to decide which way to go.";
    printf("%d\n", strlen(text));
    writeFile(&fs, "text.txt", text);
    readFile(&fs, "text.txt");
    deleteFile(&fs, "text.txt"); // 5
    displayFileSystem(&fs.tobj);
    sortDirByName(&fs.tobj, "/usr"); // 9
    searchDir(&fs.tobj,"/usr/PES"); // 10
    displayFileSystem(&fs.tobj);
    deleteDir(&fs.tobj,"DEL");
    renameDir(&fs.tobj,"NEWNAME"); // 13 
    copyDir(&fs.tobj, "/NEWNAME/PES", "/"); // 11
    printf("%s\n",fs.tobj.current_dir->name);
    displayFileSystem(&fs.tobj);
    changeCurrentDir(&fs.tobj, "PES");
    readFile(&fs, "test.txt");
    formatFS(&fs); // 8
    displayFileSystem(&fs.tobj);

    //  copyDir(&fs.tobj, "/usr/PES", "/bin");
    //  deleteDir(&fs.tobj, user_name);
    //  deleteDir(&fs.tobj, "PES");
    /*     printf("-----------MANUAL-----------\n");
        printf("1. Create Directory\n2."); */
} 

// MENU DRIVEN CODE

/* int main()
{
    FILE_SYSTEM fs;
    initializeFS(&fs);
    printf("-----------Bootup Successful-----------\n");
    createDir(&fs.tobj, "bin", 0755);
    fs.tobj.current_dir = fs.tobj.root;
    createDir(&fs.tobj, "usr", 0755);
    char user_name[20];
    char password[20];
    printf("Enter Username\n");
    scanf("%s", user_name);
    fflush(stdin);
    printf("Enter password\n");
    scanf("%s", password);
    changeCurrentDir(&fs.tobj, "/usr");
    createDir(&fs.tobj, user_name, 0755);
    int choice;
    char path[MAX_NAME_LENGTH * 10];
    char content[50000];
    int permissions;
    printf("-----------MANUAL-----------\n");
    printf("1.Create Directory : mkdir\n2.Create File : touch\n3.Write File : cat\n4.Read File : read\n5.Delete File : rm\n6.Sort By Name : sort\n7.Search Dir : search\n8.Display File System : display\n9.Delete Directory : rmdir\n10.Copy Dir : copy\n11.Move Dir : mv\n12.Rename Dir : rename\n13.Format FS : format\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter path\n");
        scanf("%s", path);
        printf("Enter permissions\n");
        scanf("%d", &permissions);
        createDir(&fs.tobj, path, permissions);
        break;
    case 2:
        printf("Enter path\n");
        scanf("%s", path);
        scanf("%d", &permissions);
        printf("Enter permissions\n");
        createFile(&fs,path,permissions);
        break;
    case 3:
        printf("Enter path\n");
        scanf("%s", path);
        writeFile(&fs,path,)
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    default:
        break;
    }
} */

/*
void deleteDirRecursiveDIR(DIRECTORY* dir, FILE_SYSTEM* fs) {
    for (int i = 0; i < dir->no_directories; i++) {
        deleteDirRecursive(&dir->subdir[i]);
    }

    for (int i = 0; i < dir->no_files; i++) {
        deleteFile(fs, dir->files[i]);
    }

    // Free the directory itself
    free(dir->files);
    free(dir);
}


void deleteDir(DIR_TREE* tobj, char path, FILE_SYSTEM fs){
    if (tobj == NULL || tobj->root == NULL || path == NULL) {
        printf("Invalid arguments.\n");
        return;
    }

    // Find the source directory
    DIRECTORY *delDir = findDir(tobj, path);
    DIRECTORY *parentDir = delDir->parentdir;

    // If source directory not found, print an error and return
    if (delDir == NULL) {
        printf("Source directory '%s' not found.\n", path);
        return;
    }

    deleteDirRecursiveDIR(delDir, fs);
    parentDir = realloc(parentDir->subdir, --(parentDir->no_directories)*sizeof(DIRECTORY));
    tobj->current_dir = parentDir;
}
*/