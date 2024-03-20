#pragma once
#include <fstream>
#include "repository.h"
#include <Windows.h>
#include <shellapi.h>
#define SW_MAXIMIZE 3

class WatchlistExporter
{
public:
	virtual void writeWatchlistToFile(Repository& watchlist) = 0;
	virtual void displayWatchlist(Repository& watchlist) {};
	WatchlistExporter() {};
	virtual ~WatchlistExporter() {};
};

class CSVExporter :public WatchlistExporter
{
public:
	CSVExporter() {};
	~CSVExporter() {};
	void writeWatchlistToFile(Repository& watchlist) override
	{
		std::cout << "Exporting watchlist to CSV...\n";
		/////
		std::ofstream fout("watchlist.csv"); // open file for writing

		if (!fout.is_open()) {
			throw std::runtime_error("Error on CSV file open");
		}

		//// Write the CSV header
		//file << "Title,Presenter,Duration,Likes,Link\n";

		for (const auto& currentTutorial : watchlist.getAllDataFromRepo()) 
		{
			fout << currentTutorial << std::endl;
		}

		fout.close();
	}
	void displayWatchlist(Repository& watchlist) override
	{
		this->writeWatchlistToFile(watchlist);
		ShellExecuteA(NULL, "open", "notepad.exe", "C:\\Users\\ACASA\\source\\repos\\a7-914-Lazar-Bianca-Maria-1\\watchlist.csv", NULL, SW_MAXIMIZE);
	}
};

class HTMLExporter :public WatchlistExporter
{
public:
	HTMLExporter() {};
	~HTMLExporter() {};
	void writeWatchlistToFile(Repository& watchlist) override
	{
		std::cout << "Exporting watchlist to HTML...\n";
		std::ofstream fout("watchlist.html");

		if (!fout.is_open()) {
			throw std::runtime_error("Error on HTML file open");
		}
		fout << "<!DOCTYPE html>\n";
		fout << "<html>\n";
		fout << "<head>\n";
		fout << "	<title>Playlist</title>\n";
		fout << "</head>\n";
		fout << "<body>\n";
		fout << "<table border=\"1\">\n";
		fout << "	<tr>\n";
		fout << "		<td>Title of tutorial</td>\n";
		fout << "		<td>Presenter name</td>\n";
		fout << "		<td>Duration</td>\n";
		fout << "		<td>Number of likes</td>\n";
		fout << "		<td>Link</td>\n";
		fout << "\t</tr>\n";
		for (const auto& currentTutorial : watchlist.getAllDataFromRepo()) {
			std::cout << "All data = " << watchlist.getRepoSize();
			fout << "\t<tr>\n";
			fout << "\t\t<td>" << currentTutorial.getTitleOfTutorial() << "</td>\n";
			fout << "\t\t<td>" << currentTutorial.getPresenterNameOfTutorial() << "</td>\n";
			fout << "\t\t<td>" << currentTutorial.getDuration() << "</td>\n";
			fout << "\t\t<td>" << currentTutorial.getNumberOfLikesOfTutorial() << "</td>\n";
			fout << "\t\t<td><a href=\"" << currentTutorial.getLink() << "\">Link</a></td>\n";
			fout << "\t</tr>\n";
		}
		fout << "</table>\n</body>\n</html>\n";
	}
	void displayWatchlist(Repository& watchlist) override
	{
		this->writeWatchlistToFile(watchlist);
		ShellExecuteA(NULL, "open", "chrome.exe", "C:\\Users\\ACASA\\source\\repos\\a7-914-Lazar-Bianca-Maria-1\\watchlist.html", NULL, SW_SHOWMAXIMIZED);
	}
};