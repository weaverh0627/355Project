/* NYSEEEEEEEEEEEEEEEEEEEM*/

//For the movie table
#include <iostream>
#include <string>
#include <stdlib.h>

/*Drivers for SQL*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main()
{
    cout << endl;

    try {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *prep_stmt;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://deltona.birdnest.org:3306", "my.weaverh3", "r780t0b1");
    /* Connect to the MySQL test database */
    con->setSchema("my_weaverh3_groupProgrammingProject");

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT Name AS _column FROM Movie");
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    string actionType;
    cout << "input what action to perform: (C for Create, R for Read, U for Update, or D for delete) " << endl;
    cin >> actionType;

    if (actionType == "C" || actionType == "c" ) {

        string movieName, description;
        int yearReleased, runtime;
        cout << "Enter The Movie Name " << endl;
        cin.ignore();
        getline(cin, movieName);
        cout << "You inputed " + movieName << endl;
        cout << "Enter The Year Released ";
        cin >> yearReleased;
        cout << "Enter the runtime of the movie " << endl;  
        cin >> runtime;
        cout << "Enter a description " << endl;  
        cin.ignore();      
        getline(cin, description);
    
        prep_stmt = con->prepareStatement("INSERT INTO Movie (Name,YearReleased,Runtime,Description) VALUES (?, ?, ?, ?)");
        prep_stmt->setString(1, movieName);
        prep_stmt->setInt(2,yearReleased);
        prep_stmt->setInt(3,runtime);
        prep_stmt->setString(4,description);
        prep_stmt->execute();

        delete prep_stmt;
        //res = stmt->executeQuery("SELECT Name AS _column FROM Movie"); 
    }

    else if (actionType == "R" || actionType == "r") {
        string columnName;
        cout << "Enter column name ";
        cin >> columnName;

        res = stmt->executeQuery("SELECT " + columnName + " AS _column FROM Movie"); 
    }

    else if (actionType == "U" || actionType == "u") {
        
        string columnName;
        columnName = "YearReleased";
        cout << "Enter an integer that is the new value for YearReleased ";
        int updatedVal, movieid;
        cin >> updatedVal;
        cout << "Enter the id number of the Movie you would like to update ";
        cin >> movieid;

        prep_stmt = con->prepareStatement("UPDATE Movie SET " + columnName + " = ? WHERE id = ?");
        prep_stmt->setInt(1,updatedVal);
        prep_stmt->setInt(2,movieid);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else if (actionType == "D" || actionType == "d") {
        //DELETE FROM table_name WHERE condition;
        int userCondition;
        cin >> userCondition;

        prep_stmt = con->prepareStatement("DELETE FROM Movie WHERE id=?");
        prep_stmt->setInt(1,userCondition);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else {
        cout << "Error: you did not enter what action you would like to perform";
    }
    
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    //DELETES FOR POINTERS DONT MESS W THIS!!!!!!!!!!!!:D
    delete res;
    delete stmt;
    delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;

    return 0;
    
}