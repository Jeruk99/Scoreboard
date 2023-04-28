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

System::Void Ponomarevivt::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void Ponomarevivt::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("��������� ��������� � ������ �������� ������ ���������� �.�. (����11)","� ���������");
	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_download_Click(System::Object^ sender, System::EventArgs^ e)
{
	//������������ � ��
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//��������� ������ � ��
	dbConnection->Open();//��������� ����������
	String^ query = "SELECT * FROM [table_name]";//������
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);//�������
	OleDbDataReader^ dbReader = dbComand->ExecuteReader();//��������� ������

	//��������� ������
	if (dbReader->HasRows == false) {
		MessageBox::Show("������ ���������� ������", "������!");
	}
	else {
		//������� ������ � ������� �����
		while (dbReader->Read()) {
			dataGridView1->Rows->Add(dbReader["id"], dbReader["way"], dbReader["data"], dbReader["time"]);
		}
	}

	//��������� ����������
	dbReader->Close();
	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	//����� ������ ������ ��� ����������
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("�������� ���� ������ ��� ����������!", "��������!");
		return;
	}

	//������ ������ ��������� ������
	int index = dataGridView1->SelectedRows[0]->Index;

	//��������� ������
	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("�� ��� ������ �������!", "��������!");
		return;
	}

	//��������� ������
	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ way = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ data = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ time = dataGridView1->Rows[index]->Cells[3]->Value->ToString();

	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "INSERT INTO [table_name] VALUES (" + id + ", '" + way + "', '" + data + "', '" + time + "')";
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);

	//��������� ������
	if (dbComand->ExecuteNonQuery() != 1)
		MessageBox::Show("������ ���������� �������!", "������!");
	else
		MessageBox::Show("������ ������� ���������", "������");

	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("�������� ���� ������ ��� ����������!", "��������!");
		return;
	}

	int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("�� ��� ������ �������!", "��������!");
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
		MessageBox::Show("������ ���������� �������!", "������!");
	else
		MessageBox::Show("������ ������� ��������", "������");

	dbConnection->Close();

	return System::Void();
}

System::Void Ponomarevivt::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("�������� ���� ������ ��� ��������!", "��������!");
		return;
	}

	int index = dataGridView1->SelectedRows[0]->Index;

	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr)
	{
		MessageBox::Show("�� ��� ������ �������!", "��������!");
		return;
	}

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();

	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "DELETE FROM [table_name] WHERE id = " + id;
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);

	if (dbComand->ExecuteNonQuery() != 1)
		MessageBox::Show("������ ���������� �������!", "������!");
	else {
		MessageBox::Show("������ ������� �������", "������!");
		dataGridView1->Rows->RemoveAt(index);
	}

	dbConnection->Close();

	return System::Void();
}
