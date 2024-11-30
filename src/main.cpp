#include "../include/set.h"

void printUsage( char* programName) {
  cerr << "�������������: " << programName << " --file <filename> --query '<command>'" << endl;
}

string Ftext(string& path, string& nameStruct) { // ������� ���������� ���� ������ ����� ��� ������ ���������
  string str, text;
  ifstream fin;
  fin.open(path);

  while (getline(fin, str)) { // ���������� ���� ������ � ����������
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens != nameStruct) {
      text += str + "\n";
    }
  }

  fin.close();
  return text;
}

void write(string& path, string& text) { // ������� ������ ������ � ����
  ofstream fout(path);
  if (!fout.is_open()) {
    cout << "�� ������� ������� ���� ��� ������" << endl;
    return;
  }
  fout << text;
  fout.close();
}

Set setReadFile(string& path, string& name) {
  Set nums; // ��������������, ��� � ��� ���� ����������� �� ��������� ��� Set
  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "�� ������� ������� ���� ��� ������" << endl;
    return nums; // ���������� ������ ���������, ���� �� ������� ������� ����
  }

  string str;
  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens == name) { // ���� ������ ������������� ����� ���������
      int key;
      while (ss >> key) { // ������ ��� ����� �� ������
        nums.add(key);
      }
      break; // ��������� ���� ����� ���������� ������ ���������
    }
  }
  fin.close();
  return nums; // ���������� ��������� ���������
}

string printHashTable( Set& set, string& name) { // ������� ��� �������� ���� ��������� ���-�������
  string str = name + ' ';
  bool first = true; // ���� ��� ���������� ��������
  for (int i = 0; i < SIZE; ++i) {
    pNode* current = set.table[i];
    while (current) {
      if (!first) {
        str += ' '; // ��������� ������ ����� ���������, ���� ��� �� ������ �������
      }
      str += to_string(current->key);
      current = current->next;
      first = false; // ����� ������� �������� ���� ��������
    }
  }
  return str;
}

void SETADD (string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
  Set nums = setReadFile(path, name);

  int key = stoi(value);
  nums.add(key);
    
  textfull += printHashTable(nums, name); // �������� ������ �� ����� ���������� ���������
  write(path, textfull); // ���������� ����������� ��������� � ����
} 

void SETDEL (string& name, string& path, string& value) {
  Set data = setReadFile(path, name);

  if (data.elementCount == 0) {
    throw out_of_range("������: ��� ������ ������ ��� �� ����");
  }
  int key = stoi(value);
  if (!data.remove(key)) { // ������� ������� �� ���������
    cerr << "������: ������� " << key << " �� ������ � ���������." << endl;
    return; // ���� ������� �� ������, ������ �������
  }

  string textfull = Ftext(path, name); // ��������� ����� ��� ������ � ���� ��� ���������� ��������

  string str = name + ' '; // ��������� ����������� ��������� � �����
  for (int i = 0; i < SIZE; ++i) {
    pNode* current = data.table[i];
      while (current) {
        str += to_string(current->key) + ' '; // ��������� ������ ����� ����������
        current = current->next;
      }
    }
  textfull += str;
  write(path, textfull); // ���������� ����������� ��������� � ����
}

bool SETHAS(string& name, string& path, string& value) {
  Set data = setReadFile(path, name); // ������ ��������� �� �����
  int key = stoi(value); // �������������� ������ � int
  return data.haveElement(key); // ��������� ������� ��������
}

void SETPRINT( string& name,  string& filename) {
  Set data = setReadFile(filename, name);

  if (data.elementCount != 0) {
    data.print();
  } else {
    throw out_of_range("������, ��� ������ ������ ��� �� ����");
  }
}

void setMenu(string& command, string& path) {
  string name, value;

  if (command.substr(0, 7) == "SETADD ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    SETADD(name, value, path);
  } else if (command.substr(0, 7) == "SETDEL ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    SETDEL(name, path, value);
  } else if (command.substr(0, 7) == "SETHAS ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    bool hasElement = SETHAS(name, path, value); // �������� ���������
    cout << (hasElement ? "������� ������." : "������� �� ������.") << endl; // ������� ���������
  } else if (command.substr(0, 9) == "SETPRINT ") {
    string cons = command.substr(9);
    stringstream stream(cons);
    stream >> name;
    SETPRINT(name, path);
  } else {
    throw out_of_range("������: ��� ����� �������");
  }
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    printUsage(argv[0]);
    return 1;
  }

  string filename; // ������ ���������� ��������� ������
  string query;

  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == "--file") {
      if (++i < argc) {
        filename = argv[i];
      } else {
        printUsage(argv[0]);
        return 1;
      }
    } else if (string(argv[i]) == "--query") {
      if (++i < argc) {
        query = argv[i];
      } else {
        printUsage(argv[0]);
        return 1;
      }
    }
  }

  if (query.empty()) { // ��������� �������
    cout << "������: ������ ���� ������� �������." << endl;
    return 1;
  }

  switch (query[0]) {
    case 'S':
    setMenu(query, filename);
    break;
    default:
    cout << "������: ����������� ��������� ������." << endl;
    return 1;
  }
  return 0;
}