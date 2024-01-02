#include "mainscreen.h"
#include "mainwindow.h"
#include "ui_mainscreen.h"
#include "datahandler.h"
#include "viewprofile.h"
#include "viewhistory.h"
#include "send_mail.h"

/*
    Definition of external variables
    - usercount: An integer representing the count of users, initialized to 0
    - user_lobby: A vector of LobbyData representing user lobby information
*/

int usercount = 0;

std::vector<LobbyData> user_lobby;

/*
    Function to create a sorted QSortFilterProxyModel for a given QSqlQueryModel
    - Create a QSortFilterProxyModel instance
    - Enable dynamic sorting and set the source model to the provided QSqlQueryModel
    - Return the sorted QSortFilterProxyModel

    Function to check if a username is already added to the user_lobby vector
    - Iterate through the user_lobby vector
    - If the username matches any entry in the vector, return true
    - If no match is found, return false
*/

QSortFilterProxyModel* getSortedModel(QSqlQueryModel* model){
    QSortFilterProxyModel *sorted_model = new QSortFilterProxyModel();
    sorted_model->setDynamicSortFilter(true);
    sorted_model->setSourceModel(model);
    return sorted_model;
}
    bool isAlreadyAdded(const QString& username){
        for(int i=0;i<usercount;i++){
        if(user_lobby[i].username == username){
            return true;
        }
    }
    return false;

}
    /*
    Function to remove a player from the user_lobby vector based on the provided username
    - Iterate through the user_lobby vector
    - If the username matches any entry in the vector, erase that entry and break from the loop
*/

void RemovePlayer(const QString& username){
    for(int i=0;i<usercount;i++){
        if(user_lobby[i].username == username){
          user_lobby.erase(user_lobby.begin()+i);
          break;
        }
    }

}

Mainscreen::Mainscreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainscreen)
{
    ui->setupUi(this);
}

Mainscreen::~Mainscreen()
{
    delete ui;
}

/*
    Override of the showEvent function for the Mainscreen class
    - Disable certain buttons if the user count is 0
    - Populate the tableWidget with data from the user_lobby vector
    - Set properties and formatting for various UI elements
    - Add items to the "game" comboBox
    - Retrieve information from the database and set up sorting for the tableView
    - Store the retrieved model in the working_model variable
    - Call the base class showEvent function
*/

void Mainscreen::Mainscreen::showEvent(QShowEvent *event)
{


    if(usercount == 0){
        this->ui->deleteUser->setDisabled(true);
        this->ui->sendInvite->setDisabled(true);
    };

    if(!user_lobby.empty()){

        for(int i=0;i<usercount;i++){
                int rowCount = this->ui->tableWidget->rowCount();
                this->ui->tableWidget->insertRow(rowCount);
                QTableWidgetItem *item = new QTableWidgetItem(user_lobby[i].username);
                QTableWidgetItem *item_two = new QTableWidgetItem(user_lobby[i].email);
                this->ui->tableWidget->setItem(rowCount,0,item);
                this->ui->tableWidget->setItem(rowCount,1,item_two);
        }


    }
    this->ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignJustify);
    this->ui->tableView->setShowGrid(false);
    this->ui->tableWidget->setShowGrid(false);
    this->ui->pushButton->setToolTip("User Profile");
    this->ui->tableView->verticalHeader()->hide();
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



    this->ui->game->addItem("Counter Strike");
    this->ui->game->addItem("Valorant");


    QSqlQueryModel* model = RetrieveInformation();
    if(model == nullptr){
         this->ui->addToParty->setEnabled(false);
    }else{

         QSortFilterProxyModel* sortedModel = getSortedModel(model);
         this->ui->tableView->setModel(sortedModel);
         this->ui->tableView->setSortingEnabled(true);



    }
    this->working_model = model;
   QMainWindow::showEvent(event);

}

/*
    Slot function for handling the button click event in the Mainscreen class
    Create an instance of the UserProfile class
    Close the current Mainscreen window
    Show the UserProfile window
*/
void Mainscreen::on_pushButton_clicked()
{
    UserProfile* userprofile = new UserProfile();
    this->close();
    userprofile->show();
}

/*
    Slot function for handling the button click event in the Mainscreen class
    Reset current user, clear user lobby, and set user count to 0
    Close the current Mainscreen window
    Create an instance of the MainWindow class
    Show the MainWindow window
*/
void Mainscreen::on_pushButton_2_clicked()
{
    CurrentUser = "";
    user_lobby.clear();
    usercount = 0;
    this->close();

    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();

}

/*
    Slot function for handling the button click event in the Mainscreen class
    Clear lineEdit, reset game and rank comboBoxes, retrieve information from the database,
    create a sorted model, and set it to the tableView
    Update the working_model variable with the retrieved model
*/
void Mainscreen::on_pushButton_3_clicked()
{
    this->ui->lineEdit->clear();
    this->ui->game->setCurrentIndex(-1);
    this->ui->rank->setCurrentIndex(-1);
    QSqlQueryModel* model = RetrieveInformation();
    QSortFilterProxyModel* sortedModel = getSortedModel(model);
    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);
    this->working_model = model;



}

/*
    Slot function for handling the currentTextChanged signal of the "game" comboBox in the Mainscreen class
    Retrieve ranks for the selected game and update the "rank" comboBox with the retrieved ranks
    Filter information based on the selected game, create a sorted model, and set it to the tableView
    Update the working_model variable with the retrieved model
*/

void Mainscreen::on_game_currentTextChanged(const QString &arg1)
{
    QStringList ranks = RetrieveRanks(arg1);
    this->ui->rank->clear();
    this->ui->rank->addItems(ranks);
    QSqlQueryModel* model = Filter(arg1);
    QSortFilterProxyModel* sortedModel = getSortedModel(model);
    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);


    this->working_model = model;



}
/*
    Slot function for handling the currentTextChanged signal of the "rank" comboBox in the Mainscreen class
    Filter information based on the selected game and rank, create a sorted model, and set it to the tableView
    Update the working_model variable with the retrieved model
*/

void Mainscreen::on_rank_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel* model = Filter(this->ui->game->currentText(),arg1);
    QSortFilterProxyModel* sortedModel = getSortedModel(model);

    this->ui->tableView->setModel(sortedModel);
    this->ui->tableView->setSortingEnabled(true);

    this->working_model = model;
}

/*
    Slot function for handling the double-clicked signal of the tableView in the Mainscreen class
    Get the index of the selected row in the tableView
    Get the model of the tableView
    Get the index of the first column in the selected row
    Retrieve the username from the data in the first column of the selected row
    Create an instance of the ViewProfile class with the retrieved username
    Show the ViewProfile window
*/
void Mainscreen::on_tableView_doubleClicked()
{
    QModelIndex selectedRow = this->ui->tableView->selectionModel()->currentIndex();

    QAbstractItemModel* model = this->ui->tableView->model();
    QModelIndex firstColumnIndex = model->index(selectedRow.row(),0);
    QString username = this->ui->tableView->model()->data(firstColumnIndex).toString();

    ViewProfile* viewprofile = new ViewProfile(username);
    viewprofile->show();
}


/*
    Slot function for handling the button click event in the Mainscreen class
    Check if the user count is less than 4
    Get the index of the selected row in the tableView
    If a row is selected:
        - Get the model of the tableView
        - Get the index of the username in the selected row
        - Retrieve the username and email from the data in the selected row
        - Check if the user is not already added to the lobby
        - If not added:
            - Insert a new row in the tableWidget with the username and email
            - Increment the user count and add the user to the user_lobby vector
            - Enable delete and sendInvite buttons
        - If the user is already added, display an information message
    If no row is selected, display an information message
    If the user count reaches 4, display an information message
    Clear the selection in the tableView
*/

void Mainscreen::on_addToParty_clicked()
{
    if(usercount<4){
         QModelIndex selectedRow = this->ui->tableView->selectionModel()->currentIndex();
         if(selectedRow.isValid()){

                QAbstractItemModel* model = this->ui->tableView->model();
                QModelIndex usernameIndex = model->index(selectedRow.row(),0);
                QString username = this->ui->tableView->model()->data(usernameIndex).toString();
                QString email = GetSpecificProfileData("email",username);
                if(!isAlreadyAdded(username)){
                    int rowCount = this->ui->tableWidget->rowCount();
                    this->ui->tableWidget->insertRow(rowCount);
                    QTableWidgetItem *item = new QTableWidgetItem(username);
                    QTableWidgetItem *item_two = new QTableWidgetItem(email);
                    this->ui->tableWidget->setItem(rowCount,0,item);
                    this->ui->tableWidget->setItem(rowCount,1,item_two);


                    usercount +=1;
                    user_lobby.push_back({username,email});
                    this->ui->deleteUser->setEnabled(true);
                    this->ui->sendInvite->setEnabled(true);

                }else{
                    QMessageBox::information(this,"Information","This User Has Already Been Added");
                }

         }else{
                QMessageBox::information(this,"Information","Consider Selecting a User first !");
         }
        this->ui->tableView->selectionModel()->clear();

    }else{
         QMessageBox::information(this,"Information","Cant Add More than 4 Users to a Lobby");
    }

}

/*
    Slot function for handling the double-clicked signal of the tableWidget in the Mainscreen class
    Get the index of the selected row in the tableWidget
    Retrieve the username from the selected row in the first column
    Create an instance of the ViewProfile class with the retrieved username
    Show the ViewProfile window
    Clear the selection in the tableWidget
*/
void Mainscreen::on_tableWidget_doubleClicked()
{

    int selectedRow = this->ui->tableWidget->selectedItems().first()->row();
    QTableWidgetItem* username = this->ui->tableWidget->item(selectedRow,0);
    ViewProfile* viewprofile = new ViewProfile(username->text());
    viewprofile->show();
    this->ui->tableWidget->selectionModel()->clear();

}
/*
    Slot function for handling the button click event in the Mainscreen class
    Get the index of the selected row in the tableWidget
    If a row is selected:
        - Retrieve the username from the selected row
        - Remove the player from the user_lobby vector
        - Remove the selected row from the tableWidget
        - Decrement the user count
        - If the user count becomes 0, disable delete and sendInvite buttons
        - Clear the selection in the tableWidget
    If no row is selected, display an information message
*/


void Mainscreen::on_deleteUser_clicked()
{

    int selectedRow = this->ui->tableWidget->currentRow();
    if(selectedRow>=0){
        QString username = this->ui->tableWidget->item(selectedRow,0)->text();
        RemovePlayer(username);
        this->ui->tableWidget->removeRow(selectedRow);
        usercount-=1;
        if(usercount==0){
                 this->ui->deleteUser->setEnabled(false);
                 this->ui->sendInvite->setEnabled(false);
        }
        this->ui->tableWidget->selectionModel()->clear();
    }else{
        QMessageBox::information(this,"Information","Select a User First !");
    }

};








void Mainscreen::on_sendInvite_clicked()
{
    if(IsDataFilled()){
        send_mail* sendinvitation= new send_mail();
        sendinvitation->exec();
    }else{
        QMessageBox::information(this,"Alert","First Fill Up Your Profile Before Sending an Invitation !");
    }
}



void Mainscreen::on_lineEdit_textChanged(const QString &arg1)
{


    if(arg1.isEmpty()){
        this->ui->tableView->setModel(this->working_model);
    }else{
        QSortFilterProxyModel* model = FilterByName(this->working_model,arg1);
        model->setParent(this);
        this->ui->tableView->setModel(model);

    }

}


void Mainscreen::on_viewHistory_clicked()
{

    ViewHistory* viewhistory = new ViewHistory();
    viewhistory->show();
}

