#pragma once

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(25, 25);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(450, 450);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(459, 433);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
	public:
		int genislik = 300, yukseklik = 300;
		int saniyeUzunluk = 130, dakikaUzunluk = 115, saatUzunluk = 80;
		int cX, cY;
		Bitmap^ btmp;
		Graphics^ g;
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		btmp = gcnew Bitmap(genislik+1,yukseklik+1);
		cX = genislik / 2;
		cY = yukseklik / 2;
		
		timer1->Start();
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	//Dakika ve saniye için kordinatlarý hesaplayan fonksiyon
	private: int* Kordinat(int val, int hlen) {
		int* kordinat = new int[2];

		val *= 6; //her dakika ve saniye 6 dereceydi
		if (val >= 0 && val <= 180) {
			kordinat[0] = cX + (int)(hlen * Math::Sin(Math::PI * val / 180));
			kordinat[1] = cY - (int)(hlen * Math::Cos(Math::PI * val / 180));
		}
		else
		{
			kordinat[0] = cX - (int)(hlen * -Math::Sin(Math::PI * val / 180));
			kordinat[1] = cY - (int)(hlen * Math::Cos(Math::PI * val / 180));
		}
		
		return kordinat;
	}

	//Saat için kordinatlarý hesaplayan fonksiyon
	private: int* sKordinat(int sval, int dval, int hlen) {
		int* kordinat = new int[2];
		//her saat 30 derece
		int val = (int)((sval * 30) + (dval * 0.5));

		if (val >= 0 && val <= 180) {
			kordinat[0] = cX + (int)(hlen * Math::Sin(Math::PI * val / 180));
			kordinat[1] = cY - (int)(hlen * Math::Cos(Math::PI * val / 180));
		}
		else {
			kordinat[0] = cX - (int)(hlen * -Math::Sin(Math::PI * val / 180));
			kordinat[1] = cY - (int)(hlen * Math::Cos(Math::PI * val / 180));
		}
		return kordinat;
	}
	
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		//grafik nesnesi oluþturma
		g = Graphics::FromImage(btmp);
		
		//Anlýk zaman deðerlerini oluþturma
		DateTime zaman = DateTime::Now;
		String^ gun = Convert::ToString(zaman.Day);
		String^ ay = Convert::ToString(zaman.Month);
		String^ yil = Convert::ToString(zaman.Year);
		String^ haftanin_gunu = Convert::ToString(zaman.DayOfWeek);
		String^ tarih = gun +"."+ ay+"."+yil;
		int snDegeri = zaman.Second;
		int dkDegeri = zaman.Minute;
		int sDegeri = zaman.Hour;
		int* koordinat;
		
		//Grafik nesnesinin içeriðini temizleme (arkayý beyaz yapar) 
		g->Clear(Color::DimGray);

		//Grafik nesnesi içine daire çizdirme
		g->DrawEllipse(gcnew Pen(Color::DarkBlue,5), 2, 2, genislik-3, yukseklik-3);
		
		//Saat içine marka yazýsý yerleþtirme
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Algerian", 20);
		SolidBrush^ renk = gcnew SolidBrush(Color::Crimson);
		g->DrawString("A&H", font, renk, PointF(117, 170));

		//Yuvarlak çizdirme
		g->DrawEllipse(gcnew Pen(Color::DarkBlue, 2), 100,150, 100, 100);
		
		//Saat içine gün,ay ve yýl bilgisi ekleme
		System::Drawing::Font^ font2 = gcnew System::Drawing::Font("Arial", 14);
		g->DrawString(tarih, font2, renk, PointF(105, 200));
		
		//Saat içine haftanýn gününü ekleme
		System::Drawing::Font^ font3 = gcnew System::Drawing::Font("Arial", 10);
		g->DrawString(haftanin_gunu, font3, renk, PointF(165, 80));
		
		//haftanýn gününü dikdörtgen içine alma
		g->DrawRectangle(gcnew Pen(Color::DarkBlue, 2), 160, 78, 60, 20);

		float r, xOrta, yOrta;
		r = (pictureBox1->Width/2)-19;
		xOrta = r; yOrta = r;
		r -= 10;
		int x1, x2, y1, y2;
		//Daire etrafýna klavuz çizgileri yerleþtirme 
		for (int aci = 0; aci <= 360; aci += 6) {
			x1 = (int)(xOrta + (r + 10) * Math::Cos(aci * 3.1415 / 180));
			y1 = (int)(yOrta - (r + 10) * Math::Sin(aci * 3.1415 / 180));
			x2 = (int)(xOrta + (r)* Math::Cos(aci * 3.1415 / 180));
			y2 = (int)(yOrta - (r)* Math::Sin(aci * 3.1415 / 180));

			//her 30 derecede kalýn çizgi(saat çizgisi)
			if (aci % 30 == 0)
				g->DrawLine(gcnew Pen(Color::Black, 4), x1, y1, x2, y2);
			else //her 6 derecede ince çizgi(dakika/saniye çizgisi)
				g->DrawLine(gcnew Pen(Color::Black, 1), x1, y1, x2, y2);
		}

		//Dairenin etrafýna sayýlarý yerleþtirme
		//Font ve Renk tanýmlama
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 16);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		//Sayýlarý yerleþtirme
		g->DrawString("1", drawFont, drawBrush, PointF(207, 27));
		g->DrawString("2", drawFont, drawBrush, PointF(255, 75));
		g->DrawString("3", drawFont, drawBrush, PointF(272, 138));
		g->DrawString("4", drawFont, drawBrush, PointF(255, 205));
		g->DrawString("5", drawFont, drawBrush, PointF(206, 252));
		g->DrawString("6", drawFont, drawBrush, PointF(140, 267));
		g->DrawString("7", drawFont, drawBrush, PointF(74, 252));
		g->DrawString("8", drawFont, drawBrush, PointF(27, 205));
		g->DrawString("9", drawFont, drawBrush, PointF(9, 138));
		g->DrawString("10", drawFont, drawBrush, PointF(23, 75));
		g->DrawString("11", drawFont, drawBrush, PointF(71, 26));
		g->DrawString("12", drawFont, drawBrush, PointF(134, 9));
		
		//Saniye gösterge konumu
		koordinat = Kordinat(snDegeri, saniyeUzunluk);
		//saniye çubuðu çizdirme
		Pen^ greenPen = gcnew Pen(Color::Orange, 1.0f);
		g->DrawLine(greenPen, cX, cY, koordinat[0], koordinat[1]);
		

		//Yelkovan konumu
		koordinat = Kordinat(dkDegeri, dakikaUzunluk);
		//Yelkovan çizdirme
		Pen^ grayPen = gcnew Pen(Color::Black, 2.0f);
		g->DrawLine(grayPen, cX, cY, koordinat[0], koordinat[1]);

		//Akrep  konumu
		koordinat = sKordinat(sDegeri % 12, dkDegeri, saatUzunluk);
		//Akrep çizdirme
		Pen^ grayPen2 = gcnew Pen(Color::Black, 4.0f);
		g->DrawLine(grayPen2, cX, cY, koordinat[0], koordinat[1]);
		
		//grafik nesnesini picturebox içerisinde gösterme
		pictureBox1->Image = btmp;
	
	}
};
}
