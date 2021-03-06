#pragma once

#include "device_io.h"

namespace WBFCaptureImage {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;

	using namespace std;

	static WINBIO_SESSION_HANDLE sessionHandle = NULL;
	static WINBIO_UNIT_ID unitId = NULL;
	static PWINBIO_BIR sample = NULL;
	static SIZE_T sampleSize = 0;
	static WINBIO_REJECT_DETAIL rejectDetail = 0;

	static vector<string> fileNameVector = vector<string>();
	static vector<string> filePathVector = vector<string>();

	int listViewItemNumber = 0;

	/// <summary>
	/// GUI 的摘要
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			image_path = Application::StartupPath + "\\Fingerprint Image\\";			
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnCaptureImage;
	protected:

	private: System::Windows::Forms::PictureBox^  pb_image;
	private: System::Windows::Forms::Button^  btnConnect;
	private: System::Windows::Forms::Label^  lbMessage;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  btnSaveImage;
	private: System::Windows::Forms::Label^  lbFileName;
	private: System::Windows::Forms::CheckBox^  cbAutoSave;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListView^  listView;
	private: System::Windows::Forms::PictureBox^  pbListViewImage;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::Label^  lbListViewFileName;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

		System::String^ image_path;

		bool autoSave;
		bool stopFlag;
		
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCaptureImage = (gcnew System::Windows::Forms::Button());
			this->pb_image = (gcnew System::Windows::Forms::PictureBox());
			this->btnConnect = (gcnew System::Windows::Forms::Button());
			this->lbMessage = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnSaveImage = (gcnew System::Windows::Forms::Button());
			this->lbFileName = (gcnew System::Windows::Forms::Label());
			this->cbAutoSave = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->pbListViewImage = (gcnew System::Windows::Forms::PictureBox());
			this->lbListViewFileName = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_image))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbListViewImage))->BeginInit();
			this->SuspendLayout();
			// 
			// btnCaptureImage
			// 
			this->btnCaptureImage->Enabled = false;
			this->btnCaptureImage->Font = (gcnew System::Drawing::Font(L"PMingLiU", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->btnCaptureImage->Location = System::Drawing::Point(12, 208);
			this->btnCaptureImage->Name = L"btnCaptureImage";
			this->btnCaptureImage->Size = System::Drawing::Size(156, 56);
			this->btnCaptureImage->TabIndex = 0;
			this->btnCaptureImage->Text = L"Capture Image";
			this->btnCaptureImage->UseVisualStyleBackColor = true;
			this->btnCaptureImage->Click += gcnew System::EventHandler(this, &GUI::btnCaptureImage_Click);
			// 
			// pb_image
			// 
			this->pb_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pb_image->Location = System::Drawing::Point(15, 21);
			this->pb_image->Name = L"pb_image";
			this->pb_image->Size = System::Drawing::Size(170, 170);
			this->pb_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb_image->TabIndex = 2;
			this->pb_image->TabStop = false;
			// 
			// btnConnect
			// 
			this->btnConnect->Font = (gcnew System::Drawing::Font(L"PMingLiU", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->btnConnect->Location = System::Drawing::Point(13, 132);
			this->btnConnect->Name = L"btnConnect";
			this->btnConnect->Size = System::Drawing::Size(155, 56);
			this->btnConnect->TabIndex = 3;
			this->btnConnect->Text = L"Connect";
			this->btnConnect->UseVisualStyleBackColor = true;
			this->btnConnect->Click += gcnew System::EventHandler(this, &GUI::btnConnect_Click);
			// 
			// lbMessage
			// 
			this->lbMessage->BackColor = System::Drawing::Color::White;
			this->lbMessage->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lbMessage->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbMessage->Location = System::Drawing::Point(13, 13);
			this->lbMessage->Name = L"lbMessage";
			this->lbMessage->Size = System::Drawing::Size(370, 105);
			this->lbMessage->TabIndex = 4;
			this->lbMessage->Text = L"Welcome use capture image tool";
			this->lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::DoWork);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::Completed);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->pb_image);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"PMingLiU", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(183, 124);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 199);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Image";
			// 
			// btnSaveImage
			// 
			this->btnSaveImage->Enabled = false;
			this->btnSaveImage->Font = (gcnew System::Drawing::Font(L"PMingLiU", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->btnSaveImage->Location = System::Drawing::Point(13, 282);
			this->btnSaveImage->Name = L"btnSaveImage";
			this->btnSaveImage->Size = System::Drawing::Size(156, 56);
			this->btnSaveImage->TabIndex = 6;
			this->btnSaveImage->Text = L"Save Image";
			this->btnSaveImage->UseVisualStyleBackColor = true;
			this->btnSaveImage->Visible = false;
			this->btnSaveImage->Click += gcnew System::EventHandler(this, &GUI::btnSaveImage_Click);
			// 
			// lbFileName
			// 
			this->lbFileName->BackColor = System::Drawing::Color::White;
			this->lbFileName->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbFileName->ForeColor = System::Drawing::Color::Red;
			this->lbFileName->Location = System::Drawing::Point(18, 91);
			this->lbFileName->Name = L"lbFileName";
			this->lbFileName->Size = System::Drawing::Size(360, 23);
			this->lbFileName->TabIndex = 7;
			this->lbFileName->Text = L"File Name : ";
			this->lbFileName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lbFileName->Visible = false;
			// 
			// cbAutoSave
			// 
			this->cbAutoSave->Enabled = false;
			this->cbAutoSave->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbAutoSave->Location = System::Drawing::Point(194, 329);
			this->cbAutoSave->Name = L"cbAutoSave";
			this->cbAutoSave->Size = System::Drawing::Size(187, 24);
			this->cbAutoSave->TabIndex = 8;
			this->cbAutoSave->Text = L"Auto Save Image";
			this->cbAutoSave->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Location = System::Drawing::Point(394, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1, 362);
			this->label1->TabIndex = 11;
			this->label1->Text = L"label1";
			// 
			// listView
			// 
			this->listView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->listView->Font = (gcnew System::Drawing::Font(L"Courier New", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView->FullRowSelect = true;
			this->listView->GridLines = true;
			this->listView->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listView->Location = System::Drawing::Point(405, 13);
			this->listView->Name = L"listView";
			this->listView->Size = System::Drawing::Size(237, 340);
			this->listView->TabIndex = 12;
			this->listView->UseCompatibleStateImageBehavior = false;
			this->listView->View = System::Windows::Forms::View::Details;
			this->listView->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::lv_SelectedIndexChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"File Name";
			this->columnHeader1->Width = 245;
			// 
			// pbListViewImage
			// 
			this->pbListViewImage->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbListViewImage->Location = System::Drawing::Point(690, 46);
			this->pbListViewImage->Name = L"pbListViewImage";
			this->pbListViewImage->Size = System::Drawing::Size(170, 170);
			this->pbListViewImage->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbListViewImage->TabIndex = 3;
			this->pbListViewImage->TabStop = false;
			// 
			// lbListViewFileName
			// 
			this->lbListViewFileName->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbListViewFileName->ForeColor = System::Drawing::Color::Red;
			this->lbListViewFileName->Location = System::Drawing::Point(648, 262);
			this->lbListViewFileName->Name = L"lbListViewFileName";
			this->lbListViewFileName->Size = System::Drawing::Size(251, 23);
			this->lbListViewFileName->TabIndex = 13;
			this->lbListViewFileName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(901, 361);
			this->Controls->Add(this->lbListViewFileName);
			this->Controls->Add(this->pbListViewImage);
			this->Controls->Add(this->listView);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cbAutoSave);
			this->Controls->Add(this->lbFileName);
			this->Controls->Add(this->btnSaveImage);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lbMessage);
			this->Controls->Add(this->btnConnect);
			this->Controls->Add(this->btnCaptureImage);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"WBFCaptureImage (1.2)";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_image))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbListViewImage))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void btnConnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 printf("\n btnConnect_Click() --> \n");

				 HRESULT hr = S_OK;
				 PWINBIO_UNIT_SCHEMA unitSchema = NULL;
				 SIZE_T unitCount = 0;
				 SIZE_T index = 0;

				 hr = WinBioEnumBiometricUnits(
					 WINBIO_TYPE_FINGERPRINT,	// Type of biometric unit
					 &unitSchema,				// Array of unit schemas
					 &unitCount					// Count of unit schemas
					 );

				 if (FAILED(hr)) {
					 printf("\n WinBioEnumBiometricUnits failed. hr = 0x%x\n", hr);
				 }

				 printf("\n unitCount: %d\n", unitCount);
				 
				 if (unitCount > 0) {	
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = "Connect success";

					 hr = WinBioOpenSession(
						 WINBIO_TYPE_FINGERPRINT,	// Service provider
						 WINBIO_POOL_SYSTEM,		// Pool type
						 WINBIO_FLAG_RAW,			// Raw access
						 NULL,						// Array of biometric unit IDs
						 0,							// Count of biometric unit IDs
						 WINBIO_DB_DEFAULT,			// Default database
						 &sessionHandle				// [out] Session handle
						 );

					 if (FAILED(hr)) {
						 printf("\n WinBioOpenSession failed. hr = 0x%x\n", hr);
					 }
					 else {
						 btnConnect->Enabled = false;
						 btnCaptureImage->Enabled = true;
						 btnSaveImage->Enabled = true;
						 cbAutoSave->Enabled = true;
					 }
				 }
				 else {
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = "Unabled to find any devices";
				 }
	}

	private: System::Void btnCaptureImage_Click(System::Object^  sender, System::EventArgs^  e) {
				 printf("\n btnCaptureImage_Click() --> \n");

				 HRESULT hr = S_OK;

				 if (cbAutoSave->CheckState == CheckState::Checked) {
					 autoSave = true;
					 if (!System::IO::Directory::Exists(image_path)) {
						 System::IO::Directory::CreateDirectory(image_path);
					 }					 
				 }
				 else {
					 autoSave = false;					 
				 }

				 if (btnCaptureImage->Text == "Capture Image") {

					 if (autoSave) {
						 lbMessage->Text = "Press finger to capture and \nsave image";
					 }
					 else {
						 lbMessage->Text = "Press finger to capture image";
					 }
					 btnCaptureImage->Text = "Stop";
					 btnSaveImage->Enabled = false;
					 cbAutoSave->Enabled = false;
					 pb_image->Image = nullptr;
					 lbFileName->Visible = false;

					 stopFlag = false;

					 backgroundWorker->RunWorkerAsync();
				 }
				 else {
					 btnCaptureImage->Text = "Capture Image";

					 backgroundWorker->CancelAsync();

					 stopFlag = true;

					 hr = WinBioCancel(sessionHandle);
					 if (FAILED(hr)) {
						 printf("\n WinBioCancel failed. hr = 0x%x\n", hr);
					 }

					 if (sample != NULL) {
						 WinBioFree(sample);
						 sample = NULL;
					 }

					 btnSaveImage->Enabled = true;
					 cbAutoSave->Enabled = true;
				 }
	}

	private: System::Void DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 printf("\n DoWork() --> \n");

				 HRESULT hr = S_OK;

				 hr = WinBioCaptureSample(
					 sessionHandle,
				     WINBIO_NO_PURPOSE_AVAILABLE,
					 WINBIO_DATA_FLAG_RAW,
					 &unitId,
					 &sample,
					 &sampleSize,
					 &rejectDetail
					 );

				 if (FAILED(hr)) {
					 if (hr == WINBIO_E_BAD_CAPTURE) {
						 printf("\n Bad capture; reason: %d\n", rejectDetail);
					 }
					 else {
						 printf("\n WinBioCaptureSample failed. hr = 0x%x\n", hr);
					 }
				 }
				 printf("\n Touch processed - Unit ID: %d\n", unitId);
				 printf("\n Capture %d bytes\n", sampleSize);
	}

	private: System::Void Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 printf("\n Completed() --> \n");

				 if (sample != NULL) {
					 //PWINBIO_BIR_HEADER BirHeader = (PWINBIO_BIR_HEADER)(((PBYTE)sample) + sample->HeaderBlock.Offset);
					 PWINBIO_BDB_ANSI_381_HEADER AnsiBdbHeader = (PWINBIO_BDB_ANSI_381_HEADER)(((PBYTE)sample) + sample->StandardDataBlock.Offset);
					 PWINBIO_BDB_ANSI_381_RECORD AnsiBdbRecord = (PWINBIO_BDB_ANSI_381_RECORD)(((PBYTE)AnsiBdbHeader) + sizeof(WINBIO_BDB_ANSI_381_HEADER));

					 DWORD width = AnsiBdbRecord->HorizontalLineLength; // Width of image in pixels
					 DWORD height = AnsiBdbRecord->VerticalLineLength; // Height of image in pixels

					 //printf("\n Image resolution: %d x %d\n", width, height);

					 PBYTE firstPixel = (PBYTE)((PBYTE)AnsiBdbRecord) + sizeof(WINBIO_BDB_ANSI_381_RECORD);

					 std::vector<uint8_t> data(width * height);
					 memcpy(&data[0], firstPixel, width * height);

					 array<Byte>^ byteArray = gcnew array<Byte>(width * height);
					 Marshal::Copy((IntPtr)data.data(), byteArray, 0, width * height);

					 pb_image->Image = ToGrayBitmap(byteArray, width, height);

					 lbMessage->Text = "Capture image success";

					 if (autoSave)  {
						 listView->Focus();
						 if (listViewItemNumber > 0) {
							 listView->Items[listViewItemNumber - 1]->Focused = false;
							 listView->Items[listViewItemNumber - 1]->Selected = false;
						 }
						 char dateTimeBuf[100];
						 char string[200];

						 SYSTEMTIME sys;
						 GetLocalTime(&sys);
						 //printf("\n %4d/%02d/%02d %02d:%02d:%02d.%01d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
						 sprintf_s(dateTimeBuf, sizeof(dateTimeBuf), "%4d%02d%02d_%02d%02d%02d%.03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);

						 strcpy_s(string, sizeof(string), (char*)(void*)Marshal::StringToHGlobalAnsi(image_path));
						 strcat_s(string, sizeof(string), "\\");
						 strcat_s(string, sizeof(string), dateTimeBuf);
						 strcat_s(string, sizeof(string), ".png");
												 
						 pb_image->Image->Save(Marshal::PtrToStringAnsi((IntPtr)string), ImageFormat::Png);

						 System::String^ fileName = Path::GetFileName(Marshal::PtrToStringAnsi((IntPtr)string));
						 System::String^ filePath = Marshal::PtrToStringAnsi((IntPtr)string);

						 listView->Items->Add(fileName);

						 lbFileName->Visible = true;
						 lbFileName->Text = "File name: " + fileName;

						 IntPtr ptrToNativeFileNameString = Marshal::StringToHGlobalAnsi(fileName);
						 char* nativeFileNameString = static_cast<char*>(ptrToNativeFileNameString.ToPointer());

						 IntPtr ptrToNativeFilePathString = Marshal::StringToHGlobalAnsi(filePath);
						 char* nativeFilePathString = static_cast<char*>(ptrToNativeFilePathString.ToPointer());

						 fileNameVector.push_back(nativeFileNameString);
						 filePathVector.push_back(nativeFilePathString);

						 listViewItemNumber = listViewItemNumber + 1;

						 listView->Items[listViewItemNumber - 1]->Focused = true;
						 listView->Items[listViewItemNumber - 1]->Selected = true;
						 listView->Items[listViewItemNumber - 1]->EnsureVisible();
					 }

					 backgroundWorker->RunWorkerAsync();
				 }

				 if (!stopFlag) {
					 if (!getDevicePath()) {
						 printf("\n GetDevicePath() fail.\n");
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Unabled to find any devices.";

						 btnCaptureImage->Text = "Capture Image";
						 btnConnect->Enabled = true;
						 btnCaptureImage->Enabled = false;
						 btnSaveImage->Enabled = false;
						 cbAutoSave->Enabled = false;
					 }
				 }
	}	

	private: System::Void btnSaveImage_Click(System::Object^  sender, System::EventArgs^  e) {

				 char dateTimeBuf[100];
				
				 SYSTEMTIME sys;
				 GetLocalTime(&sys);
				 sprintf_s(dateTimeBuf, sizeof(dateTimeBuf), "%4d%02d%02d_%02d%02d%02d%.03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);

				 SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
				 saveFileDialog->Filter = "PNG Image|*.png";

				 if (!System::IO::Directory::Exists(image_path)) {
					 System::IO::Directory::CreateDirectory(image_path);
					 saveFileDialog->InitialDirectory = image_path;
				 }
				 else {
					 saveFileDialog->InitialDirectory = image_path;
				 }

				 saveFileDialog->Title = "Save an Image File";
				 saveFileDialog->FileName = Marshal::PtrToStringAnsi((IntPtr)dateTimeBuf);

				 if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK && saveFileDialog->FileName != "") {
					 pb_image->Image->Save(saveFileDialog->FileName, ImageFormat::Png);

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = "Save image success";
					 lbFileName->Visible = true;
					 lbFileName->Text = "File name: " + Path::GetFileName(saveFileDialog->FileName);

					 listView->Items->Add(Path::GetFileName(saveFileDialog->FileName));

					 IntPtr ptrToNativeFileNameString = Marshal::StringToHGlobalAnsi(Path::GetFileName(saveFileDialog->FileName));
					 char* nativeFileNameString = static_cast<char*>(ptrToNativeFileNameString.ToPointer());

					 IntPtr ptrToNativeFilePathString = Marshal::StringToHGlobalAnsi(saveFileDialog->FileName);
					 char* nativeFilePathString = static_cast<char*>(ptrToNativeFilePathString.ToPointer());

					 fileNameVector.push_back(nativeFileNameString);
					 filePathVector.push_back(nativeFilePathString);

					 listView->Focus();
					 if (listViewItemNumber > 0) {
						 listView->Items[listViewItemNumber - 1]->Focused = false;
						 listView->Items[listViewItemNumber - 1]->Selected = false;
					 }

					 listViewItemNumber = listViewItemNumber + 1;

					 listView->Items[listViewItemNumber - 1]->Focused = true;
					 listView->Items[listViewItemNumber - 1]->Selected = true;
					 listView->Items[listViewItemNumber - 1]->EnsureVisible();
				 }
	}

	public: static Bitmap^ ToGrayBitmap(array<Byte>^ rawValues, int width, int height) {
				Bitmap^ bmp = gcnew Bitmap(width, height, System::Drawing::Imaging::PixelFormat::Format8bppIndexed);
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
				BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::WriteOnly, bmp->PixelFormat);

				int stride = bmpData->Stride;
				int offset = stride - width;
				IntPtr iptr = bmpData->Scan0;
				int scanBytes = stride * height;

				int posScan = 0, posReal = 0;

				array<Byte>^ pixelValues = gcnew array<Byte>(scanBytes);

				for (int x = 0; x < height; x++) {
					for (int y = 0; y < width; y++) {
						pixelValues[posScan++] = rawValues[posReal++];
					}
					posScan += offset;
				}

				Marshal::Copy(pixelValues, 0, iptr, scanBytes);
				bmp->UnlockBits(bmpData);

				ColorPalette^ temPalette;

				Bitmap^ tempBmp = gcnew Bitmap(1, 1, System::Drawing::Imaging::PixelFormat::Format8bppIndexed);
				temPalette = tempBmp->Palette;

				for (int i = 0; i < 256; i++) {
					temPalette->Entries[i] = Color::FromArgb(i, i, i);
				}

				bmp->Palette = temPalette;

				return bmp;
	}

	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
				 backgroundWorker->WorkerSupportsCancellation = true;

				 list_files();

				 checkListViewItem(image_path);
	}

	private: void checkListViewItem(System::String^ path)
	{
				 std::vector<string> FILENAME = vector<string>();
				 std::vector<string> FILEPATH = vector<string>();

				 //if (System::IO::Directory::Exists(Marshal::PtrToStringAnsi((IntPtr)path)))
				 if (System::IO::Directory::Exists(path)) {
					 //array<System::String^>^ file = Directory::GetFiles(Marshal::PtrToStringAnsi((IntPtr)path));
					 array<System::String^>^ file = Directory::GetFiles(path);
					 array<System::DateTime^>^ dateTime = gcnew array<System::DateTime^>(file->Length);

					 if (file->Length > 0) {
						 listView->Focus();
						 /*
						 for (int x = 0; x < file->Length; x++)
						 {
						 FileInfo^ sfi = gcnew FileInfo(file->GetValue(x)->ToString());
						 dateTime[x] = sfi->LastWriteTime;
						 Console::WriteLine("name : " + sfi->Name);
						 Console::WriteLine("time : " + dateTime[x]);
						 }

						 Array::Sort(dateTime, file);
						 */

						 for (int i = 0; i < file->Length; i++) {

							 System::String^ file_name = Path::GetFileName(file[i]);
							 System::String^ file_path = file[i];

							 //System::String^ splite_file_name = file_name->Substring(0, file_name->Length - 4);

							 //listView->Items->Add(splite_file_name);
							 listView->Items->Add(file_name);

							 //IntPtr ptrToNativeFileNameString = Marshal::StringToHGlobalAnsi(splite_file_name);
							 //char* nativeFileNameString = static_cast<char*>(ptrToNativeFileNameString.ToPointer());

							 IntPtr ptrToNativeFileNameString = Marshal::StringToHGlobalAnsi(file_name);
							 char* nativeFileNameString = static_cast<char*>(ptrToNativeFileNameString.ToPointer());

							 IntPtr ptrToNativeFilePathString = Marshal::StringToHGlobalAnsi(file_path);
							 char* nativeFilePathString = static_cast<char*>(ptrToNativeFilePathString.ToPointer());
						 							 
							 fileNameVector.push_back(nativeFileNameString);
							 filePathVector.push_back(nativeFilePathString);							
						 }
						 listViewItemNumber = file->Length;

						 listView->Items[listViewItemNumber - 1]->Focused = true;
						 listView->Items[listViewItemNumber - 1]->Selected = true;
						 listView->Items[listViewItemNumber - 1]->EnsureVisible();
					 }
				 }
	}

	private: array<System::String^>^ list_files() {
				 System::String^ DS_file = ".DS_Store";

				 if (System::IO::Directory::Exists(image_path)) {
					 array<System::String^>^ file = Directory::GetFiles(image_path);
					 array<System::String^>^ fileList = gcnew array<System::String^>(file->Length);

					 for (int i = 0; i < file->Length; i++) {
						 if (DS_file == Path::GetFileName(file[i])) {
							 printf("\n delete file name => %s\n", file[i]);
							 remove((char*)(void*)Marshal::StringToHGlobalAnsi(file[i]));
						 }
						 else {
							 fileList[i] = Path::GetFileName(file[i]);
						 }
					 }
					 printf("\n file length => %d\n", file->Length);
					 return fileList;
				 }
	}

	private: System::Void lv_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

				 if (listView->SelectedItems->Count > 0) {
					 //printf("\n lv_SelectedIndexChanged\n");
					 for (int i = 0; i < listViewItemNumber; i++) {
						 if (listView->Items[i]->Selected == true) {							 
							 System::String^ strName = gcnew System::String(fileNameVector[i].c_str());
							 System::String^ strPath = gcnew System::String(filePathVector[i].c_str());

							 pbListViewImage->Image = Image::FromFile(strPath);
							 lbListViewFileName->Text = strName;
						 }
					 }
				 }
	}
};
}
