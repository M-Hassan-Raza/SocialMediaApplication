#include <iostream>
#include <fstream>

using namespace std;

class Object;
class Page;
class User;
class Date;
class Facebook;
class Post;
class Activity;


class HelperClass
{
public:
	static int sizeOfString(char* str)
	{
		int stringLen = 0;
		for (char* count = str; *count != '\0'; count++)
		{
			stringLen++;
		}

		return stringLen;
	}

	static char* GetStringFromBuffer(char* buffer)
	{
		int strSize = sizeOfString(buffer);
		char* dataDestination = 0;

		if (strSize > 0)
		{
			dataDestination = new char[strSize+1];


			for(int i = 0; buffer[i] != '\0'; i++)
			{
				dataDestination[i] = buffer[i];
			}

			dataDestination[strSize] = '\0';
		}
		return dataDestination;
	}

	static bool Search(char* str1, char* str2)
	{
		int sizeStr1 = sizeOfString(str1);
		int sizeStr2 = sizeOfString(str2);
		bool found;

		for(int i = 0; i < sizeStr1; i++)
		{ 
			if(tolower(str2[0]) == tolower(str1[i]))
			{
				found = true;

				for(int k = 1; (k < sizeStr2) && (found == true); k++)
				{
					if(tolower(str1[i+k]) != tolower(str2[k]))
					{
						found = false;
					}
				}

				if(found == true)
				{
					return true;
				}
			}
		}

		return false;
	}

};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Date
{
private:
	static int day;
	static int month;
	static int year;

public:
	static Date currentDate;
	Date()
	{
		day = 1;
		month = 1;
		year = 1927;
	}
	bool isLatestDate()
	{
		if ((day == currentDate.day - 1) || (day == currentDate.day))
		{
			if ((month == currentDate.month) && (year == currentDate.year))
			{
				return true;
			}
		}
		return false;
	}
	Date(int, int, int);
	~Date();
	static void setDate(int, int, int);
	static void PrintDate();
	void LoadDateFromFile(ifstream&);
};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Object
{
public:
	char* ID;
	Object();
	virtual ~Object();
	virtual void PrintIDAndName()
	{

	}
	virtual void PrintID()
	{

	}
	virtual void PrintName()
	{

	}
	virtual char* GetID()
	{
		return ID;
	}
	virtual void SetTimeline(Post*&)
	{

	}
	void PrintAuthor()
	{
		cout << "\t";

		PrintID();

		cout << "  :  ";

		PrintName();

		cout << endl;
	}

};
Object::Object()
{
	ID = NULL;
}

Object::~Object()
{
	if(ID != NULL)
	{
		delete[] ID;
		ID = NULL;
	}
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Comment
{
private:
	Object* author;
	char* text;
	char* ID;

public:
	static int totalComments;
	Comment();
	~Comment();
	void SetCommentValues(char*, char*, Object*);
	void ViewComment();
	void AddComment(Object*, char*);
};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Post
{
private:
	char* ID;
	char* text;
	int numberOfComments;
	Comment** comments;
	Object** likedBy;

protected:
	Object* author;
	Date postedOn;

public:
	Post();
	virtual ~Post();
	Object* GetAuthor()
	{
		return author;
	}
	void SetAuthor(Object*& auth)
	{
		author = auth;
		numberOfPosts++;
	}
	int numberOfLikes;
	int numberOfPosts;
	char* GetPostID();
	Comment** GetComments()
	{
		return comments;
	}
	int GetNumberOfLikes()
	{
		return numberOfLikes;
	}
	void SetTotalLikes(int);
	virtual void LoadPostFromTextFile(ifstream&);
	void LikePost(User*);
	void ViewLikedBy();
	void SetComments(Comment* comments_)
	{
		if(comments == NULL)
		{
			comments = new Comment*[10];
		}

		comments[numberOfComments++] = comments_;
	}
	virtual void ViewPost()
	{
		cout<<endl<<"---";
		author->PrintName();
		cout<<"shared "<< "\"" << text << "\"\n\t";
		ViewAllComments();

	}
	void ViewAllComments();
	void ViewlikedList();
	virtual void print();
	void SetLikedBy(Object* Like, int x)
	{
		if (likedBy == NULL)
		{
			likedBy = new Object * [10];            // total ten Users or Pages can like a post 
		}

		if (x < 10)
		{
			likedBy[x] = Like;
		}
	}
	char* GetText();
	void PrintIDAndName();
	void AddComment(Comment*);
	Date* GetDate()
	{
		return &postedOn;
	}
	virtual void PrintWithDate();
	virtual void ViewPostWithoutComments();
};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Activity: public Post
{
private:
	int type;
	char* value;

public:
	Activity();
	~Activity();
	void LoadPostFromTextFile(ifstream&);
	void Print();
	virtual void ViewPost();
	void ViewPostWithoutComments();
	void PrintWithDate();
};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Page : public Object
{
private:	
	int numberOfPosts;
	int totalPosts;
	char* Title;
	Post** timeline;
public:
	Page();
	~Page();
	char* GetPageID();
	char* GetPageTitle();
	void PrintPage();
	void PrintName();
	void PrintID();
	void ViewTimeline();
	void PrintIDAndName();
	void SetTimeline(Post*);
	void PrintLikedPagePosts();
	Page* loadPageFromTextFile(ifstream&);

};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class User : public Object
{
private:
	char* FirstName;
	char* LastName;
	int numberOfLikedPages;
	int numberOfFriends;
	int totalPosts;
	int numberOfPosts;
	User** FriendList;
	Page** LikedPages;
	Post** timeline;
public:
	User();
	~User();
	void PrintIDAndName();
	User* loadUserFromTextFile(ifstream&, char**&, char**&);
	void SetTotalFriends(int);
	void PrintLikedPagePosts();
	void ViewLikedPages();
	void ViewFriendList();
	void ViewHomepage();
	void ViewTimeline();
	void SetTimeline(Post*);
	void ViewLikedList();
	void PostComment();
	void ViewPost();
	void PrintID();
	void PrintName();
	void LikeAPost(char*);
	char* GetUserID();
	char* GetFirstName();
	char* GetLastName();
	User**& GetFriendList();
	Page**& GetLikedPages();
	void PrintUser();
	void AddFriend(User*&, int);
	void AddPage(Page*&, int);
	void PrintFriendsPosts();
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Facebook
{
private:
	int numberOfPages;
	int numberOfUsers;
	int numberOfPosts;
	int numberOfComments;
	User* CurrentUser;
	User** UsersList;
	Page** PageList;
	Post** postsList;
	Comment** allComments;

public:
	Facebook();
	~Facebook();
	Page*& SearchPageByID(char*);
	User*& SearchUserByID(char*);
	Post*& SearchPostByID(char*);
	void LoadData(char***&, char***&);
	void LoadAllPosts();
	void LoadAllComments();
	void LoadAllUsers();
	void LoadAllPages();
	void SetCurrentUser(char*);
	void AddFriends(char***&);
	void AddPages(char***&);
	void RunTheProgram();
	void LikeAPost(char*);
	void ViewLikesofPost(char*);
	void LeaveCommentOnPost(char*, char*);
	void ViewPage(char*);
	void SearchEverything(char*);
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Date::day = 15;
int Date::month = 11;
int Date::year = 2017;
int Comment::totalComments = 0;

void main()
{
	Facebook fb;
	char*** tempFriendList;
	char*** tempLikedPages;

	fb.LoadData(tempFriendList, tempLikedPages);
	fb.AddFriends(tempFriendList);
	fb.AddPages(tempLikedPages);

	fb.RunTheProgram();
	//system("pause>0");
}

//------------------------------------------------------------------ User Functionality --------------------------------------------------------------------

User::User()
{
	ID = NULL;
	LastName = NULL;
	FirstName = NULL;
	FriendList = NULL;
	LikedPages = NULL;
	numberOfFriends = 0;
	numberOfLikedPages = 0;
	numberOfPosts = 0;
	totalPosts = 0;
	timeline = NULL;
}

User::~User()
{
	cout << "~User Called\n";

	if(ID != NULL)
	{
		delete[] ID;
		ID = NULL;
	}

	if(FirstName != NULL)
	{
		delete[] FirstName;
		FirstName = NULL;
	}

	if(LastName != NULL)
	{
		delete[] LastName;
		LastName = NULL;
	}

	if(FriendList != NULL)
	{
		delete[] FriendList;
		FriendList = NULL;
	}


	if(LikedPages != NULL)
	{
		delete[] LikedPages;
		LikedPages = NULL;
	}

	if(timeline != NULL)
	{
		for(int i = 0; i < numberOfPosts; i++)
		{
			if(timeline[i] != NULL)
			{
				delete[] timeline[i];
			}
		}

		delete[] timeline;
		timeline = NULL;
	}
}

void User::ViewLikedPages()
{
	cout << "\nCommand:\tView Liked Pages\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << FirstName << " " << LastName << "\t\t-\tLiked Pages\n\n";

	for(int i = 0; i < numberOfLikedPages ; i++)
	{
		LikedPages[i]->PrintPage();
	}

	cout << "------------------------------------------------------------------------------------------------------------------\n";

	return;
}

void User::PrintUser()
{
	cout << ID << "\t-\t" << FirstName << " " << LastName << endl;
}

void User::ViewFriendList()
{
	cout << "\nCommand:\tView Friend List\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << FirstName << " " << LastName << "\t\t-\tFriend List\n\n";

	for(int i = 0;i < numberOfFriends; i++)
	{
		FriendList[i]->PrintUser();
	}

	cout << "------------------------------------------------------------------------------------------------------------------\n";

	return;
}

User* User::loadUserFromTextFile(ifstream& inputUser, char**& tempFriends, char**& tempPageLikes)
{
	char tempUserID[5];
	char tempFirstName[20];
	char tempLastName[20];
	char tempFriend[5];
	char tempPage[5];
	numberOfFriends = -1;
	numberOfLikedPages = -1;

	tempFriends = new char*[10];
	tempPageLikes = new char*[10];
	timeline = new Post*[10];
	for(int i = 0; i < 10; i++)
	{
		tempFriends[i] = new char;
		tempPageLikes[i] = new char;
		timeline[i] = NULL;
	}


	inputUser >> tempUserID >> tempFirstName >> tempLastName;

	ID = HelperClass::GetStringFromBuffer(tempUserID);
	FirstName = HelperClass::GetStringFromBuffer(tempFirstName);
	LastName = HelperClass::GetStringFromBuffer(tempLastName);

	for(int i = 0; tempFriend[0] != '-'; i++, numberOfFriends++)
	{
		inputUser >> tempFriend;
		tempFriends[i] = HelperClass::GetStringFromBuffer(tempFriend);
	}

	for(int i = 0; tempPage[0] != '-'; i++, numberOfLikedPages++)
	{
		inputUser >> tempPage;
		tempPageLikes[i] = HelperClass::GetStringFromBuffer(tempPage);
	}


	return this;
}

char* User::GetUserID()
{
	return ID;
}

char* User::GetFirstName()
{
	return FirstName;
}

char* User::GetLastName()
{
	return LastName;
}

User**& User::GetFriendList()
{
	return FriendList;
}

Page**& User::GetLikedPages()
{
	return LikedPages;
}

void User::AddFriend(User*& friendPointer, int indexOfFriend)
{
	if(FriendList == NULL)
	{
		FriendList = new User*[10];
	}

	if(indexOfFriend <= 10)
	{
		FriendList[indexOfFriend] = friendPointer;
	}

	return;
}

void User::AddPage(Page*& pagePointer, int indexOfPage)
{
	if(LikedPages == NULL)
	{
		LikedPages = new Page*[10];
	}

	if(indexOfPage <= 10)
	{
		LikedPages[indexOfPage] = pagePointer;
	}

	return;
}

void User::PrintIDAndName()
{
	cout << ID << " -- " << FirstName << " " << LastName; 
}

void User::PrintFriendsPosts()
{
	for(int i = 0; i < numberOfPosts; i++)
	{
		Date* date = timeline[i]->GetDate();
		if(date->isLatestDate() == true)
		{
			timeline[i]->print();
		}
	}
}

void User::SetTotalFriends(int _friends)
{
	numberOfFriends = _friends;
}

void User::ViewHomepage()
{
	cout << "\nCommands:\tView Home\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << FirstName << " " << LastName << " - Homepage\n\n";

	for(int i = 0; i < numberOfFriends; i++)
	{
		FriendList[i]->PrintFriendsPosts();
	}

	for(int i = 0; i < numberOfLikedPages; i++)
	{
		LikedPages[i]->PrintLikedPagePosts();
	}
}

void User::ViewTimeline()
{
	cout << "\nCommand:\tView Timeline\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << FirstName << " " << LastName <<  "'s Timeline.\n\n";
	for(int i = 0; i < numberOfPosts; i++)
	{
		timeline[i]->ViewPost();
		cout << "\n\n";
	}

}

void User::LikeAPost(char* postID)
{

}

void User::SetTimeline(Post* post)
{
	if(timeline == NULL)
	{
		timeline = new Post*[10];
	}
	timeline[numberOfPosts++] = post;
}

void User::PrintName()
{
	cout << FirstName << " " << LastName << " " ;
}

void User::PrintID()
{
	cout << ID << " ";
}


//----------------------------------------------------------------------- Page Functionality -------------------------------------------------------------------

Page::Page()
{
	ID = NULL;
	Title = NULL;
	timeline = NULL;
	numberOfPosts = 0;
}

Page::~Page()
{
	cout << "~Page() called\n";
	if(ID != NULL)
	{
		delete[] ID;
		ID = NULL;
	}

	if(Title != NULL)
	{
		delete[] Title;
		Title = NULL;
	}
	if(timeline != NULL)
	{
		for(int i = 0; i < numberOfPosts; i++)
		{
			if(timeline[i] != NULL)
			{
				delete[] timeline[i];
			}
		}

		delete[] timeline;
		timeline = NULL;
	}
}

void Page::PrintPage()
{
	cout << ID << "\t-\t" << Title << endl;
}

Page* Page::loadPageFromTextFile(ifstream& inputPage)
{
	int counter1 = 0;
	int counter2 = 0;
	char tempPageID[5];
	char tempPageTitle[50];
	char tempLine[100];

	inputPage.getline(tempLine, 100);

	for(; tempLine[counter1] != ' '; counter1++)
	{
		tempPageID[counter1] = tempLine[counter1];
	}
	tempPageID[counter1++] = '\0';


	for(; tempLine[counter1] != '\0'; counter1++)
	{
		tempPageTitle[counter2++] = tempLine[counter1];
	}
	tempPageTitle[counter2] = '\0';


	ID = HelperClass::GetStringFromBuffer(tempPageID);
	Title = HelperClass::GetStringFromBuffer(tempPageTitle);


	return this;
}

char* Page::GetPageID()
{
	return ID;
}

char* Page::GetPageTitle()
{
	return Title;
}

void Page::ViewTimeline()
{
	for(int i = 0; i < numberOfPosts; i++)
	{
		timeline[i]->ViewPost();
		cout << "\n\n";
	}

}

void Page::PrintIDAndName()
{
	cout << ID << " -- " << Title;
}

void Page::SetTimeline(Post* post)
{
	if(timeline == NULL)
	{
		timeline = new Post*[10];
	}
	timeline[numberOfPosts++] = post;
}

void Page::PrintName()
{
	cout << Title << " ";
}

void Page::PrintID()
{
	cout << ID << " ";
}

void Page::PrintLikedPagePosts()
{
	for(int i = 0; i < numberOfPosts; i++)
	{
		timeline[i]->print();
	}
}


//------------------------------------------------------------------------- Facebook Functionality -----------------------------------------------------------------------------

Facebook::Facebook()
{
	numberOfPages = 0;
	numberOfUsers = 0;
	CurrentUser = NULL;
	UsersList = NULL;
	PageList = NULL;
}

Facebook::~Facebook()
{
	cout << "~Facebook Called\n";
	if(UsersList != NULL)
	{
		for(int i = 0; i < numberOfUsers; i++)
		{
			if(UsersList[i] != NULL)
			{
				delete UsersList[i];
			}
		}

		delete[] UsersList;
		UsersList = NULL;
	}

	if(PageList != NULL)
	{
		for(int i = 0; i < numberOfPages; i++)
		{
			if(PageList[i] != NULL)
			{
				delete PageList[i];
			}
		}

		delete[] PageList;
		PageList = NULL;
	}

	if(postsList != NULL)
	{
	delete[] postsList;
	}

}

void Facebook::LoadData(char*** &tempFriendList, char*** &tempLikedPages)
{
	ifstream inputUsers("Users.txt");

	if(!inputUsers)
	{
		cout << "User Text File couldn't be loaded for some reason. Please verify the location of the file.\n";
		return;
	}

	inputUsers >> numberOfUsers;
	inputUsers.ignore(1);

	tempFriendList = new char**[numberOfUsers];
	tempLikedPages = new char**[numberOfUsers];
	UsersList = new User*[numberOfUsers];

	for(int i = 0; i < numberOfUsers; i++)
	{
		UsersList[i] = new User;
		UsersList[i]->loadUserFromTextFile(inputUsers, tempFriendList[i], tempLikedPages[i]);
	}
	inputUsers.close();



	ifstream inputPages("Pages.txt");
	if(!inputPages)
	{
		cout << "Pages Text File couldn't be loaded for some reason. Please verify the location of the file.\n";
		return;
	}

	inputPages >> numberOfPages;
	inputPages.ignore(1);
	PageList = new Page*[numberOfPages];

	for(int i = 0; i < numberOfPages; i++)
	{
		PageList[i] = new Page;
		PageList[i]->loadPageFromTextFile(inputPages);
	}

	inputPages.close();

	return;
}

void Facebook::LoadAllPosts()
{
	int postType;
	char tempSharedBy[5];

	ifstream inputPosts("Posts.txt");
	if(!inputPosts)
	{
		cout << "Posts Text File couldn't be loaded for some reason. Please verify the location of the file.\n";
		return;
	}

	inputPosts >> numberOfPosts;
	postsList = new Post*[numberOfPosts];

	for(int i = 0; i < numberOfPosts; i++)
	{
		inputPosts >> postType;
		if(postType == 2)
		{
			postsList[i] = new Activity;
		}
		else
		{
			postsList[i] = new Post;
		}

		postsList[i]->LoadPostFromTextFile(inputPosts);

		inputPosts >> tempSharedBy;
		Object* Author;

		if(tempSharedBy[0] == 'u')
		{
			Author = SearchUserByID(tempSharedBy);
		}
		else if(tempSharedBy[0] == 'p')
		{
			Author = SearchPageByID(tempSharedBy);
		}

		postsList[i]->SetAuthor(Author);

		Author->SetTimeline(postsList[i]);

		char tempLikedBy[10][10];
		int totalLikes = 0;

		for(; ; totalLikes++)
		{
			inputPosts >> tempLikedBy[totalLikes];

			if(tempLikedBy[totalLikes][0] == '-')
			{
				break;
			}
		}
		if(totalLikes > 10)
		{
			totalLikes = 10;
		}

		postsList[i]->SetTotalLikes(totalLikes);

		for(int k = 0; k < totalLikes; k++)
		{
			if(tempLikedBy[k][0] == 'u')
			{
				postsList[i]->SetLikedBy(SearchUserByID(tempLikedBy[k]), k);
			}
			else if(tempLikedBy[k][0] == 'p')
			{
				postsList[i]->SetLikedBy(SearchPageByID(tempLikedBy[k]), k);
			}
		}

		totalLikes = 0;

	}
}

void Facebook::LoadAllComments()
{
	char temporaryBuffer[20];
	char* tempCommentID;
	char* tempPostID;
	char* tempAuthor;
	char* tempCommentText;
	char tempText[200];
	Object* CommentBy;
	Post* tempPost;

	ifstream inputComments("Comments.txt");
	if(!inputComments)
	{
		cout << "Comments Text File couldn't be loaded for some reason. Please verify the location of the file.\n";
		return;
	}


	inputComments >> numberOfComments;
	allComments = new Comment*[numberOfComments];


	for(int i = 0; i < numberOfComments; i++)
	{
		allComments[i] = new Comment;

		inputComments >> temporaryBuffer;
		tempCommentID = HelperClass::GetStringFromBuffer(temporaryBuffer);

		inputComments.ignore();
		inputComments >> temporaryBuffer;
		tempPostID = HelperClass::GetStringFromBuffer(temporaryBuffer);

		inputComments >> temporaryBuffer;
		tempAuthor = HelperClass::GetStringFromBuffer(temporaryBuffer);

		inputComments.getline(tempText, 200);
		tempCommentText = HelperClass::GetStringFromBuffer(tempText);

		if(tempAuthor[0] == 'u')
		{
			CommentBy = SearchUserByID(tempAuthor);
		}
		else if(tempAuthor[0] == 'p')
		{
			CommentBy = SearchPageByID(tempAuthor);
		}

		allComments[i]->SetCommentValues(tempCommentID, tempCommentText, CommentBy);

		tempPost = SearchPostByID(tempPostID);
		tempPost->SetComments(allComments[i]);
	}
}

Page*& Facebook::SearchPageByID(char* pageID)
{
	bool foundID;
	int sizeOfID = HelperClass::sizeOfString(pageID);

	for(int i = 0; i < numberOfPages; i++)
	{
		if(PageList[i]->GetPageID()[0] == pageID[0])
		{
			foundID = true;

			for(int j = 1; (j < sizeOfID) && (foundID == true); j++)
			{
				if(PageList[i]->GetPageID()[j] != pageID[j])
				{
					foundID = false;
				}
			}

			if(foundID == true)
			{
				return PageList[i];
			}
		}

	}

	//return NULL;

}

User*& Facebook::SearchUserByID(char* userID)
{
	bool foundID;
	int sizeOfID = HelperClass::sizeOfString(userID);

	for(int i = 0; i < numberOfUsers; i++)
	{
		if(UsersList[i]->GetUserID()[0] == userID[0])
		{
			foundID = true;

			for(int j = 1; (j < sizeOfID) && (foundID == true); j++)
			{
				if(UsersList[i]->GetUserID()[j] != userID[j])
				{
					foundID = false;
				}
			}

			if(foundID == true)
			{
				return UsersList[i];
			}
		}

	}

	//return NULL;
}

void Facebook::AddFriends(char***& listOfFriends)
{

	for(int i = 0; i < numberOfUsers; i++)
	{
		for(int j = 0; listOfFriends[i][j][0] == 'u'; j++)
		{
			UsersList[i]->AddFriend(SearchUserByID(listOfFriends[i][j]), j);
		}
	}

	//De-allocate the triple pointer as we have no need of this anymore, the association is already done. 
	if(listOfFriends != NULL)
	{
		for(int i = 0; i < numberOfUsers; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				if(listOfFriends[i][j] != NULL)
				{
					delete[] listOfFriends[i][j];
				}		
			}
			delete[] listOfFriends[i];
		}

		delete[] listOfFriends;
		listOfFriends = NULL;
	}


	return;
}

void Facebook::AddPages(char***& listOfPages)
{
	for(int i = 0; i < numberOfUsers; i++)
	{
		for(int j = 0; listOfPages[i][j][0] == 'p'; j++)
		{
			UsersList[i]->AddPage(SearchPageByID(listOfPages[i][j]), j);
		}
	}


	//De-allocate the triple pointer as we have no need of this anymore, the association is already done. 
	if(listOfPages != NULL)
	{
		for(int i = 0; i < numberOfUsers; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				if(listOfPages[i][j] != NULL)
				{
					delete[] listOfPages[i][j];
				}		
			}
			delete[] listOfPages[i];
		}

		delete[] listOfPages;
		listOfPages = NULL;
	}


	return;
}

void Facebook::SetCurrentUser(char* userID)
{
	cout << "Command:\tSet current user\"" << userID << "\"\n"; 

	if(SearchUserByID(userID) != NULL)
	{
		CurrentUser = SearchUserByID(userID);
		cout << "\n" << CurrentUser->GetFirstName() << " " << CurrentUser->GetLastName() << " successfully set as the Current User.\n";
	}
	else
	{
		cout << "Error occured while setting the current user. Please make sure that the student exists.\n";
	}

	return;
}

void Facebook::ViewLikesofPost(char* post)
{
	cout << "\n\nCommand:\tViewLikedList(" << post << ")\n";
	Post* temp;
	temp = SearchPostByID(post);
	temp->ViewlikedList();
}

void Facebook::LikeAPost(char* post)
{
	cout << "\n\nCommand:\tLikePost(" << post << ")\n";
	Post* temp;
	temp = SearchPostByID(post);
	temp->LikePost(CurrentUser);
}

void Facebook::LeaveCommentOnPost(char* postID, char* text)
{
	cout << "\nCommand:\t PostComment(" << postID << ", " << text << ") " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------\n";

	Comment* comment = new Comment();
	numberOfComments++;
	comment->SetCommentValues("", text, CurrentUser);
	Post* post = SearchPostByID(postID);
	post->AddComment(comment);

}

void Facebook::ViewPage(char* pageID)
{
	cout << "\nCommand:\t ViewPage(" << pageID << ") " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	Page* page = SearchPageByID(pageID);
	page->ViewTimeline();

}

void Facebook::SearchEverything(char* search)
{
	cout << "\n\n\nCommand:\t Search(\"" << search << "\") " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	bool usersFound = false;
	bool postsFound = false;
	bool pagesFound = false;
	int counter = 0;


	for(int i = 0; i < numberOfUsers; i++)
	{
		char* temp = UsersList[i]->GetFirstName();

		if((HelperClass::Search(temp, search) == true))
		{
			usersFound = true;
			counter++;
			if(counter == 1)
			{
				cout << "Users: \n";
			}
			UsersList[i]->PrintIDAndName();
			cout << endl;
		}

	}

	counter = 0;
	for(int i = 0; i < numberOfUsers; i++)
	{
		char* temp = UsersList[i]->GetLastName();
		if((HelperClass::Search(temp, search) == true))
		{
			usersFound = true;
			counter++;
			if(counter == 1)
			{
				cout << "Users: \n";
			}
			UsersList[i]->PrintIDAndName();
			cout << endl;
		}

	}


	counter = 0;

	for(int i = 0; i < numberOfPosts; i++)
	{
		char* temp = postsList[i]->GetText();
		if((HelperClass::Search(temp, search) == true))
		{
			postsFound = true;
			counter++;
			if(counter == 1)
			{
				cout << "Posts: \n";
			}

			postsList[i]->ViewPostWithoutComments();
			cout << endl;
		}

	}
	if(postsFound == false)
	{
		cout << "No posts found.\n";
	}


	counter = 0;
	for(int i = 0; i < numberOfPages; i++)
	{
		char* temp = PageList[i]->GetPageTitle();
		if((HelperClass::Search(temp, search) == true))
		{
			pagesFound = true;
			counter++;
			if(counter == 1)
			{
				cout << "\n\nPages: \n\n";
			}
			PageList[i]->PrintName();
		}

	}
	if(pagesFound == false)
	{
		cout << "No pages found.\n";
	}

}

void Facebook::RunTheProgram()
{

	SetCurrentUser("u7");
	Date::setDate(15, 11, 2017);
	cout << "System Date:\t";
	Date::PrintDate();

	CurrentUser->ViewFriendList();
	CurrentUser->ViewLikedPages();

	CurrentUser->PrintName();

	LoadAllPosts();
	LoadAllComments();

	CurrentUser->ViewHomepage();

	CurrentUser->ViewTimeline();

	ViewLikesofPost("post5");
	LikeAPost("post5");
	ViewLikesofPost("post5");

	LeaveCommentOnPost("post4", "good luck for your result!");
	Post* post = SearchPostByID("post4");
	post->ViewPost();

	LeaveCommentOnPost("post8", "Thanks for the Wishes");
	Post* post2 = SearchPostByID("post8");
	post2->ViewPost();

	ViewPage("p1");
	SearchEverything("Birthday");
	SearchEverything("Ali");


	system("pause>0");

	return;
}

//------------------------------------------------------------------------- Comment Functionality -----------------------------------------------------------------------------

Comment::Comment()
{
	author = NULL;
	text = NULL;
	ID = NULL;
}

Comment::~Comment()
{
	cout << "~Comment() called\n";
	if(text != NULL)
	{
		delete[] text;
		text = NULL;
	}

	if(ID != NULL)
	{
		delete[] ID;
		ID = NULL;
	}
}

void Comment::AddComment(Object* auth, char* newComment)
{
	Comment::totalComments++;
	author = auth;
	char tempCommentID[5], NumericalID[5];
	_itoa_s(Comment::totalComments, NumericalID, 5);
	NumericalID[HelperClass::sizeOfString(NumericalID)] = '\0';
	strcat_s(tempCommentID, NumericalID);
	ID = HelperClass::GetStringFromBuffer(tempCommentID);
	text = HelperClass::GetStringFromBuffer(newComment);
}


void Comment::ViewComment()
{
	author->PrintName();
	cout << "wrote:\t" << "\"" << text << "\"";
}

void Comment::SetCommentValues(char* comID, char* comText, Object* Author)
{
	ID = comID;
	text = comText;
	author = Author;
}


//------------------------------------------------------------------------- Posts Functionality -----------------------------------------------------------------------------

Post::Post()
{
	numberOfComments = 0;
	numberOfLikes = 0;
	numberOfPosts = 0;
	ID = NULL;
	text = NULL;
	author = NULL;
	comments = NULL;
	likedBy = NULL;
}

Post::~Post()
{
	cout << "~Post() called\n";
	if(ID != NULL)
	{
		delete[] ID;
		ID = NULL;
	}

	if(text != NULL)
	{
		delete[] text;
		text = NULL;
	}


	if(comments != NULL)
	{
		for(int i = 0; i < numberOfComments; i++)
		{
			if(comments[i] != NULL)
			{
				delete comments[i];
			}

		}
		delete[] comments;
		comments = NULL;
	}

	if(likedBy != NULL)
	{
		delete[] likedBy;
		likedBy = NULL;
	}
}

void Post::LoadPostFromTextFile(ifstream& inputPost)
{
	char tempPostID[10];
	char tempPostText[200];

	inputPost >> tempPostID;
	postedOn.LoadDateFromFile(inputPost);

	inputPost.ignore();
	inputPost.getline(tempPostText, 200, '\n');

	text = HelperClass::GetStringFromBuffer(tempPostText);
	ID = HelperClass::GetStringFromBuffer(tempPostID);

}

void Post::LikePost(User* liker)
{
	bool alreadyLiked = false;

	if (numberOfLikes < 10)
	{
		for (int i = 0; i < numberOfLikes; i++)
		{
			if (likedBy[i] == liker)
			{
				cout << "\nPost already liked!\n";
				alreadyLiked = true;
			}
		}
		if (alreadyLiked == false)
		{
			likedBy[numberOfLikes++] = liker;
		}
	}
}

void Post::print()
{
	cout <<  "\n\n---";
	author->PrintName();
	cout << " shared " << "\"" << text << "\"" << " \n";
	ViewAllComments();
}

Post*& Facebook::SearchPostByID(char* PostID)
{
	bool foundID;
	int sizeOfID = HelperClass::sizeOfString(PostID);

	for(int i = 0; i < numberOfPosts; i++)
	{
		if(postsList[i]->GetPostID()[0] == PostID[0])
		{
			foundID = true;

			for(int j = 1; (j < sizeOfID) && (foundID == true); j++)
			{
				if(postsList[i]->GetPostID()[j] != PostID[j])
				{
					foundID = false;
				}
			}

			if(foundID == true)
			{
				return postsList[i];
			}
		}

	}

}

char* Post::GetPostID()
{
	return ID;
}

void Post::ViewAllComments()
{
	for(int i = 0; i < numberOfComments; i++)
	{
		cout<<endl;
		cout<<"\t\t\t";
		comments[i]->ViewComment();		
	}
}

void Post::SetTotalLikes(int _likes)
{
	numberOfLikes = _likes;
}

char* Post::GetText()
{
	return text;
}

void Post::AddComment(Comment* comment)
{
	if(numberOfComments < 10)
	{
		comments[numberOfComments++] = comment;
	}

}

void Post::ViewlikedList()
{
	cout << "Post Liked By:\n";

	for(int i = 0; i < numberOfLikes; i++)
	{
		if(likedBy[i] != NULL)
		{
			likedBy[i]->PrintIDAndName();
			cout << endl;
		}
	}

}

void Post::PrintWithDate()
{
	cout <<  "\n\n---";
	author->PrintName();
	cout << " shared " << "\"" << text << "\"" << " ";
	ViewAllComments();
	postedOn.PrintDate();
}

void Post::ViewPostWithoutComments()
{
	cout <<  "\n\n---";
	author->PrintName();
	cout << " shared " << "\"" << text << "\"" << " ";
}


//---------------------------------------------------------------------------------------------------------------------------------

Activity::Activity(): Post()
{
	type = 0;
	value = NULL;
}

Activity::~Activity()
{
	cout << "~Activity() called\n";
	if(value != NULL)
	{
		delete[] value;
		value = NULL;
	}
}

void Activity::LoadPostFromTextFile(ifstream& inputPost)
{
	Post::LoadPostFromTextFile(inputPost);

	inputPost >> type;
	char tempValue[200];
	inputPost.getline(tempValue, 200);
	value = HelperClass::GetStringFromBuffer(tempValue);
}

void Activity::ViewPost()
{
	cout << endl << endl << "---";
	author->PrintName();

	if(value != 0)
	{
		cout << " is ";

		if(type == 1)
		{
			cout << "feeling";
		}
		else if (type == 2)
		{
			cout << "thinking about";
		}
		else if(type == 3)
		{
			cout << "making";
		}
		else if (type == 4)
		{
			cout << "celebrating";
		}

		cout << "\"" << value << "\"" << " ";
		cout << "\n\n";
	}

	Post::ViewAllComments();

}

void Activity::PrintWithDate()
{
	ViewPost();
	cout << " ... (";
	postedOn.PrintDate();
	cout << ")";
}

void Activity::ViewPostWithoutComments()
{
	cout << endl << endl << "---";
	author->PrintName();

	if(value != 0)
	{
		cout << " is ";

		if(type == 1)
		{
			cout << "feeling";
		}
		else if (type == 2)
		{
			cout << "thinking about";
		}
		else if(type == 3)
		{
			cout << "making";
		}
		else if (type == 4)
		{
			cout << "celebrating";
		}

		cout << " \"" << value << "\"" << " ";
		cout << "\n\n";
	}
	cout << " ... (";
	postedOn.PrintDate();
	cout << ")";
}


//-------------------------------------------------------------------------------------------------------------------------------------

Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

Date::~Date()
{
	cout << "~Date() Called\n";
}

void Date::LoadDateFromFile(ifstream& input)
{
	input >> day >> month >> year;

}

void Date::PrintDate()
{
	cout << day << "/" << month << "/" << year;
}

void Date::setDate(int d, int m, int y)
{
	cout << "\nCommand:\tSet Current System Date " << d << " " << m << " " << y << endl;
	day = d;
	month = m;
	year = y;
}
