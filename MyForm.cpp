#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;

[STAThread]
int main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Ponomarevivt::MyForm form;
	Application::Run(% form);
}

System::Void Ponomarevivt::MyForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void Ponomarevivt::MyForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Программа выполнена в рамках курсовой работы Пономарева В.А. (ИВТб11)","О программе");
	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_download_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Подключаемся к БД
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//Выполняем запрос к БД
	dbConnection->Open();//открываем соединение
	String^ query = "SELECT * FROM [table_name]";//запрос
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);//команда
	OleDbDataReader^ dbReader = dbComand->ExecuteReader();//считываем данные

	//Проверяем данные
	if (dbReader->HasRows == false) {
		MessageBox::Show("Ошибка считывания данных", "Ошибка!");
	}
	else {
		//добавим данные в таблицу формы
		while (dbReader->Read()) {
			dataGridView1->Rows->Add(dbReader["id"], dbReader["way"], dbReader["data"], dbReader["time"]);
		}
	}

	//Закрываем соединение
	dbReader->Close();
	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Выбор нужной строки для добавления
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите одну строку для добавления!", "Внимание!");
		return;
	}

	//Узнаем индекс выбранной строки
	int index = dataGridView1->SelectedRows[0]->Index;

	//Проверяем данные
	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("Не все данные введены!", "Внимание!");
		return;
	}

	//Считываем данные
	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ way = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ data = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ time = dataGridView1->Rows[index]->Cells[3]->Value->ToString();

	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "INSERT INTO [table_name] VALUES (" + id + ", '" + way + "', '" + data + "', '" + time + "')";
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);

	//Выполняем запрос
	if (dbComand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
	else
		MessageBox::Show("Данные успешно добавлены", "Готово");

	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите одну строку для обновления!", "Внимание!");
		return;
	}

	int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("Не все данные введены!", "Внимание!");
		return;
	}

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ way = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ data = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ time = dataGridView1->Rows[index]->Cells[3]->Value->ToString();

	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "UPDATE [table_name] SET [Way]='"+ way +"', [Data] = '"+ data +"', [Time]='"+ time +"' WHERE [id] = " + id;
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);

 	if (dbComand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
	else
		MessageBox::Show("Данные успешно изменены", "Готово");

	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выберите одну строку для удаления!", "Внимание!");
		return;
	}

	int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr)
	{
		MessageBox::Show("Не все данные введены!", "Внимание!");
		return;
	}

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();

	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "DELETE FROM [table_name] WHERE id = " + id;
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);

	if (dbComand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
	else {
		MessageBox::Show("Данные успешно удалены", "Готово!");
		dataGridView1->Rows->RemoveAt(index);
	}

	dbConnection->Close();

	return System::Void();
}
